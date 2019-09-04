#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int completed; scalar_t__ waiting; } ;
struct drbd_request {unsigned int rq_state; scalar_t__ epoch; int /*<<< orphan*/  req_pending_master_completion; TYPE_1__ i; TYPE_4__* master_bio; int /*<<< orphan*/  tl_requests; int /*<<< orphan*/  private_bio; struct drbd_device* device; } ;
struct drbd_device {int /*<<< orphan*/  misc_wait; } ;
struct bio_and_error {TYPE_4__* bio; int /*<<< orphan*/  error; } ;
struct TYPE_8__ {int bi_opf; } ;
struct TYPE_7__ {TYPE_2__* connection; } ;
struct TYPE_6__ {int /*<<< orphan*/  current_tle_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ REQ_OP_READ ; 
 int REQ_RAHEAD ; 
 unsigned int const RQ_COMPLETION_SUSP ; 
 unsigned int const RQ_LOCAL_ABORTED ; 
 unsigned int const RQ_LOCAL_OK ; 
 unsigned int const RQ_LOCAL_PENDING ; 
 unsigned int const RQ_NET_OK ; 
 unsigned int const RQ_NET_PENDING ; 
 unsigned int const RQ_NET_QUEUED ; 
 int RQ_POSTPONED ; 
 int /*<<< orphan*/  _drbd_end_io_acct (struct drbd_device*,struct drbd_request*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_op (TYPE_4__*) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,...) ; 
 TYPE_3__* first_peer_device (struct drbd_device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ op_is_write (scalar_t__) ; 
 int /*<<< orphan*/  start_new_tl_epoch (TYPE_2__*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void drbd_req_complete(struct drbd_request *req, struct bio_and_error *m)
{
	const unsigned s = req->rq_state;
	struct drbd_device *device = req->device;
	int error, ok;

	/* we must not complete the master bio, while it is
	 *	still being processed by _drbd_send_zc_bio (drbd_send_dblock)
	 *	not yet acknowledged by the peer
	 *	not yet completed by the local io subsystem
	 * these flags may get cleared in any order by
	 *	the worker,
	 *	the receiver,
	 *	the bio_endio completion callbacks.
	 */
	if ((s & RQ_LOCAL_PENDING && !(s & RQ_LOCAL_ABORTED)) ||
	    (s & RQ_NET_QUEUED) || (s & RQ_NET_PENDING) ||
	    (s & RQ_COMPLETION_SUSP)) {
		drbd_err(device, "drbd_req_complete: Logic BUG rq_state = 0x%x\n", s);
		return;
	}

	if (!req->master_bio) {
		drbd_err(device, "drbd_req_complete: Logic BUG, master_bio == NULL!\n");
		return;
	}

	/*
	 * figure out whether to report success or failure.
	 *
	 * report success when at least one of the operations succeeded.
	 * or, to put the other way,
	 * only report failure, when both operations failed.
	 *
	 * what to do about the failures is handled elsewhere.
	 * what we need to do here is just: complete the master_bio.
	 *
	 * local completion error, if any, has been stored as ERR_PTR
	 * in private_bio within drbd_request_endio.
	 */
	ok = (s & RQ_LOCAL_OK) || (s & RQ_NET_OK);
	error = PTR_ERR(req->private_bio);

	/* Before we can signal completion to the upper layers,
	 * we may need to close the current transfer log epoch.
	 * We are within the request lock, so we can simply compare
	 * the request epoch number with the current transfer log
	 * epoch number.  If they match, increase the current_tle_nr,
	 * and reset the transfer log epoch write_cnt.
	 */
	if (op_is_write(bio_op(req->master_bio)) &&
	    req->epoch == atomic_read(&first_peer_device(device)->connection->current_tle_nr))
		start_new_tl_epoch(first_peer_device(device)->connection);

	/* Update disk stats */
	_drbd_end_io_acct(device, req);

	/* If READ failed,
	 * have it be pushed back to the retry work queue,
	 * so it will re-enter __drbd_make_request(),
	 * and be re-assigned to a suitable local or remote path,
	 * or failed if we do not have access to good data anymore.
	 *
	 * Unless it was failed early by __drbd_make_request(),
	 * because no path was available, in which case
	 * it was not even added to the transfer_log.
	 *
	 * read-ahead may fail, and will not be retried.
	 *
	 * WRITE should have used all available paths already.
	 */
	if (!ok &&
	    bio_op(req->master_bio) == REQ_OP_READ &&
	    !(req->master_bio->bi_opf & REQ_RAHEAD) &&
	    !list_empty(&req->tl_requests))
		req->rq_state |= RQ_POSTPONED;

	if (!(req->rq_state & RQ_POSTPONED)) {
		m->error = ok ? 0 : (error ?: -EIO);
		m->bio = req->master_bio;
		req->master_bio = NULL;
		/* We leave it in the tree, to be able to verify later
		 * write-acks in protocol != C during resync.
		 * But we mark it as "complete", so it won't be counted as
		 * conflict in a multi-primary setup. */
		req->i.completed = true;
	}

	if (req->i.waiting)
		wake_up(&device->misc_wait);

	/* Either we are about to complete to upper layers,
	 * or we will restart this request.
	 * In either case, the request object will be destroyed soon,
	 * so better remove it from all lists. */
	list_del_init(&req->req_pending_master_completion);
}