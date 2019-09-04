#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_conf {int wire_protocol; int max_epoch_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  cb; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/  waiting; int /*<<< orphan*/  sector; } ;
struct drbd_request {int rq_state; TYPE_1__ w; int /*<<< orphan*/  master_bio; TYPE_2__ i; struct drbd_device* device; } ;
struct drbd_peer_device {struct drbd_connection* connection; } ;
struct drbd_device {int writ_cnt; int read_cnt; int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  flags; int /*<<< orphan*/  write_requests; int /*<<< orphan*/  read_requests; } ;
struct drbd_connection {int current_tle_writes; int /*<<< orphan*/  sender_work; int /*<<< orphan*/  net_conf; } ;
struct bio_and_error {int /*<<< orphan*/ * bio; } ;
typedef  enum drbd_req_event { ____Placeholder_drbd_req_event } drbd_req_event ;

/* Variables and functions */
#define  ABORT_DISK_IO 157 
#define  BARRIER_ACKED 156 
#define  COMPLETED_OK 155 
#define  CONFLICT_RESOLVED 154 
#define  CONNECTION_LOST_WHILE_PENDING 153 
#define  DATA_RECEIVED 152 
#define  DISCARD_COMPLETED_NOTSUPP 151 
#define  DISCARD_COMPLETED_WITH_ERROR 150 
 int DRBD_PROT_B ; 
 int DRBD_PROT_C ; 
 int /*<<< orphan*/  DRBD_READ_ERROR ; 
 int /*<<< orphan*/  DRBD_WRITE_ERROR ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device* const,int) ; 
#define  FAIL_FROZEN_DISK_IO 149 
#define  HANDED_OVER_TO_NETWORK 148 
 int MR_READ ; 
 int MR_WRITE ; 
#define  NEG_ACKED 147 
#define  OOS_HANDED_TO_NETWORK 146 
#define  POSTPONE_WRITE 145 
#define  QUEUE_AS_DRBD_BARRIER 144 
#define  QUEUE_FOR_NET_READ 143 
#define  QUEUE_FOR_NET_WRITE 142 
#define  QUEUE_FOR_SEND_OOS 141 
#define  READ_AHEAD_COMPLETED_WITH_ERROR 140 
#define  READ_COMPLETED_WITH_ERROR 139 
#define  READ_RETRY_REMOTE_CANCELED 138 
#define  RECV_ACKED_BY_PEER 137 
#define  RESEND 136 
#define  RESTART_FROZEN_DISK_IO 135 
 int RQ_COMPLETION_SUSP ; 
 int RQ_EXP_BARR_ACK ; 
 int RQ_EXP_RECEIVE_ACK ; 
 int RQ_EXP_WRITE_ACK ; 
 int RQ_LOCAL_ABORTED ; 
 int RQ_LOCAL_COMPLETED ; 
 int RQ_LOCAL_MASK ; 
 int RQ_LOCAL_OK ; 
 int RQ_LOCAL_PENDING ; 
 int RQ_NET_DONE ; 
 int RQ_NET_MASK ; 
 int RQ_NET_OK ; 
 int RQ_NET_PENDING ; 
 int RQ_NET_QUEUED ; 
 int RQ_NET_SENT ; 
 int RQ_NET_SIS ; 
 int RQ_POSTPONED ; 
 int RQ_WRITE ; 
#define  SEND_CANCELED 134 
#define  SEND_FAILED 133 
#define  TO_BE_SENT 132 
#define  TO_BE_SUBMITTED 131 
 int /*<<< orphan*/  UNPLUG_REMOTE ; 
 int /*<<< orphan*/  WRITE ; 
#define  WRITE_ACKED_BY_PEER 130 
#define  WRITE_ACKED_BY_PEER_AND_SIS 129 
#define  WRITE_COMPLETED_WITH_ERROR 128 
 int /*<<< orphan*/  __drbd_chk_io_error (struct drbd_device* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_data_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device* const,char*,...) ; 
 int /*<<< orphan*/  drbd_insert_interval (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int drbd_interval_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  drbd_queue_work (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  drbd_report_io_error (struct drbd_device* const,struct drbd_request*) ; 
 int /*<<< orphan*/  drbd_set_out_of_sync (struct drbd_device* const,int /*<<< orphan*/ ,int) ; 
 struct drbd_peer_device* first_peer_device (struct drbd_device* const) ; 
 int /*<<< orphan*/  get_ldev (struct drbd_device* const) ; 
 int /*<<< orphan*/  is_pending_write_protocol_A (struct drbd_request*) ; 
 int /*<<< orphan*/  mod_rq_state (struct drbd_request*,struct bio_and_error*,int,int) ; 
 struct net_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_new_tl_epoch (struct drbd_connection* const) ; 
 int /*<<< orphan*/  w_restart_disk_io ; 
 int /*<<< orphan*/  w_send_dblock ; 
 int /*<<< orphan*/  w_send_out_of_sync ; 
 int /*<<< orphan*/  w_send_read_req ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int __req_mod(struct drbd_request *req, enum drbd_req_event what,
		struct bio_and_error *m)
{
	struct drbd_device *const device = req->device;
	struct drbd_peer_device *const peer_device = first_peer_device(device);
	struct drbd_connection *const connection = peer_device ? peer_device->connection : NULL;
	struct net_conf *nc;
	int p, rv = 0;

	if (m)
		m->bio = NULL;

	switch (what) {
	default:
		drbd_err(device, "LOGIC BUG in %s:%u\n", __FILE__ , __LINE__);
		break;

	/* does not happen...
	 * initialization done in drbd_req_new
	case CREATED:
		break;
		*/

	case TO_BE_SENT: /* via network */
		/* reached via __drbd_make_request
		 * and from w_read_retry_remote */
		D_ASSERT(device, !(req->rq_state & RQ_NET_MASK));
		rcu_read_lock();
		nc = rcu_dereference(connection->net_conf);
		p = nc->wire_protocol;
		rcu_read_unlock();
		req->rq_state |=
			p == DRBD_PROT_C ? RQ_EXP_WRITE_ACK :
			p == DRBD_PROT_B ? RQ_EXP_RECEIVE_ACK : 0;
		mod_rq_state(req, m, 0, RQ_NET_PENDING);
		break;

	case TO_BE_SUBMITTED: /* locally */
		/* reached via __drbd_make_request */
		D_ASSERT(device, !(req->rq_state & RQ_LOCAL_MASK));
		mod_rq_state(req, m, 0, RQ_LOCAL_PENDING);
		break;

	case COMPLETED_OK:
		if (req->rq_state & RQ_WRITE)
			device->writ_cnt += req->i.size >> 9;
		else
			device->read_cnt += req->i.size >> 9;

		mod_rq_state(req, m, RQ_LOCAL_PENDING,
				RQ_LOCAL_COMPLETED|RQ_LOCAL_OK);
		break;

	case ABORT_DISK_IO:
		mod_rq_state(req, m, 0, RQ_LOCAL_ABORTED);
		break;

	case WRITE_COMPLETED_WITH_ERROR:
		drbd_report_io_error(device, req);
		__drbd_chk_io_error(device, DRBD_WRITE_ERROR);
		mod_rq_state(req, m, RQ_LOCAL_PENDING, RQ_LOCAL_COMPLETED);
		break;

	case READ_COMPLETED_WITH_ERROR:
		drbd_set_out_of_sync(device, req->i.sector, req->i.size);
		drbd_report_io_error(device, req);
		__drbd_chk_io_error(device, DRBD_READ_ERROR);
		/* fall through. */
	case READ_AHEAD_COMPLETED_WITH_ERROR:
		/* it is legal to fail read-ahead, no __drbd_chk_io_error in that case. */
		mod_rq_state(req, m, RQ_LOCAL_PENDING, RQ_LOCAL_COMPLETED);
		break;

	case DISCARD_COMPLETED_NOTSUPP:
	case DISCARD_COMPLETED_WITH_ERROR:
		/* I'd rather not detach from local disk just because it
		 * failed a REQ_DISCARD. */
		mod_rq_state(req, m, RQ_LOCAL_PENDING, RQ_LOCAL_COMPLETED);
		break;

	case QUEUE_FOR_NET_READ:
		/* READ, and
		 * no local disk,
		 * or target area marked as invalid,
		 * or just got an io-error. */
		/* from __drbd_make_request
		 * or from bio_endio during read io-error recovery */

		/* So we can verify the handle in the answer packet.
		 * Corresponding drbd_remove_request_interval is in
		 * drbd_req_complete() */
		D_ASSERT(device, drbd_interval_empty(&req->i));
		drbd_insert_interval(&device->read_requests, &req->i);

		set_bit(UNPLUG_REMOTE, &device->flags);

		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		D_ASSERT(device, (req->rq_state & RQ_LOCAL_MASK) == 0);
		mod_rq_state(req, m, 0, RQ_NET_QUEUED);
		req->w.cb = w_send_read_req;
		drbd_queue_work(&connection->sender_work,
				&req->w);
		break;

	case QUEUE_FOR_NET_WRITE:
		/* assert something? */
		/* from __drbd_make_request only */

		/* Corresponding drbd_remove_request_interval is in
		 * drbd_req_complete() */
		D_ASSERT(device, drbd_interval_empty(&req->i));
		drbd_insert_interval(&device->write_requests, &req->i);

		/* NOTE
		 * In case the req ended up on the transfer log before being
		 * queued on the worker, it could lead to this request being
		 * missed during cleanup after connection loss.
		 * So we have to do both operations here,
		 * within the same lock that protects the transfer log.
		 *
		 * _req_add_to_epoch(req); this has to be after the
		 * _maybe_start_new_epoch(req); which happened in
		 * __drbd_make_request, because we now may set the bit
		 * again ourselves to close the current epoch.
		 *
		 * Add req to the (now) current epoch (barrier). */

		/* otherwise we may lose an unplug, which may cause some remote
		 * io-scheduler timeout to expire, increasing maximum latency,
		 * hurting performance. */
		set_bit(UNPLUG_REMOTE, &device->flags);

		/* queue work item to send data */
		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		mod_rq_state(req, m, 0, RQ_NET_QUEUED|RQ_EXP_BARR_ACK);
		req->w.cb =  w_send_dblock;
		drbd_queue_work(&connection->sender_work,
				&req->w);

		/* close the epoch, in case it outgrew the limit */
		rcu_read_lock();
		nc = rcu_dereference(connection->net_conf);
		p = nc->max_epoch_size;
		rcu_read_unlock();
		if (connection->current_tle_writes >= p)
			start_new_tl_epoch(connection);

		break;

	case QUEUE_FOR_SEND_OOS:
		mod_rq_state(req, m, 0, RQ_NET_QUEUED);
		req->w.cb =  w_send_out_of_sync;
		drbd_queue_work(&connection->sender_work,
				&req->w);
		break;

	case READ_RETRY_REMOTE_CANCELED:
	case SEND_CANCELED:
	case SEND_FAILED:
		/* real cleanup will be done from tl_clear.  just update flags
		 * so it is no longer marked as on the worker queue */
		mod_rq_state(req, m, RQ_NET_QUEUED, 0);
		break;

	case HANDED_OVER_TO_NETWORK:
		/* assert something? */
		if (is_pending_write_protocol_A(req))
			/* this is what is dangerous about protocol A:
			 * pretend it was successfully written on the peer. */
			mod_rq_state(req, m, RQ_NET_QUEUED|RQ_NET_PENDING,
						RQ_NET_SENT|RQ_NET_OK);
		else
			mod_rq_state(req, m, RQ_NET_QUEUED, RQ_NET_SENT);
		/* It is still not yet RQ_NET_DONE until the
		 * corresponding epoch barrier got acked as well,
		 * so we know what to dirty on connection loss. */
		break;

	case OOS_HANDED_TO_NETWORK:
		/* Was not set PENDING, no longer QUEUED, so is now DONE
		 * as far as this connection is concerned. */
		mod_rq_state(req, m, RQ_NET_QUEUED, RQ_NET_DONE);
		break;

	case CONNECTION_LOST_WHILE_PENDING:
		/* transfer log cleanup after connection loss */
		mod_rq_state(req, m,
				RQ_NET_OK|RQ_NET_PENDING|RQ_COMPLETION_SUSP,
				RQ_NET_DONE);
		break;

	case CONFLICT_RESOLVED:
		/* for superseded conflicting writes of multiple primaries,
		 * there is no need to keep anything in the tl, potential
		 * node crashes are covered by the activity log.
		 *
		 * If this request had been marked as RQ_POSTPONED before,
		 * it will actually not be completed, but "restarted",
		 * resubmitted from the retry worker context. */
		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		D_ASSERT(device, req->rq_state & RQ_EXP_WRITE_ACK);
		mod_rq_state(req, m, RQ_NET_PENDING, RQ_NET_DONE|RQ_NET_OK);
		break;

	case WRITE_ACKED_BY_PEER_AND_SIS:
		req->rq_state |= RQ_NET_SIS;
	case WRITE_ACKED_BY_PEER:
		/* Normal operation protocol C: successfully written on peer.
		 * During resync, even in protocol != C,
		 * we requested an explicit write ack anyways.
		 * Which means we cannot even assert anything here.
		 * Nothing more to do here.
		 * We want to keep the tl in place for all protocols, to cater
		 * for volatile write-back caches on lower level devices. */
		goto ack_common;
	case RECV_ACKED_BY_PEER:
		D_ASSERT(device, req->rq_state & RQ_EXP_RECEIVE_ACK);
		/* protocol B; pretends to be successfully written on peer.
		 * see also notes above in HANDED_OVER_TO_NETWORK about
		 * protocol != C */
	ack_common:
		mod_rq_state(req, m, RQ_NET_PENDING, RQ_NET_OK);
		break;

	case POSTPONE_WRITE:
		D_ASSERT(device, req->rq_state & RQ_EXP_WRITE_ACK);
		/* If this node has already detected the write conflict, the
		 * worker will be waiting on misc_wait.  Wake it up once this
		 * request has completed locally.
		 */
		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		req->rq_state |= RQ_POSTPONED;
		if (req->i.waiting)
			wake_up(&device->misc_wait);
		/* Do not clear RQ_NET_PENDING. This request will make further
		 * progress via restart_conflicting_writes() or
		 * fail_postponed_requests(). Hopefully. */
		break;

	case NEG_ACKED:
		mod_rq_state(req, m, RQ_NET_OK|RQ_NET_PENDING, 0);
		break;

	case FAIL_FROZEN_DISK_IO:
		if (!(req->rq_state & RQ_LOCAL_COMPLETED))
			break;
		mod_rq_state(req, m, RQ_COMPLETION_SUSP, 0);
		break;

	case RESTART_FROZEN_DISK_IO:
		if (!(req->rq_state & RQ_LOCAL_COMPLETED))
			break;

		mod_rq_state(req, m,
				RQ_COMPLETION_SUSP|RQ_LOCAL_COMPLETED,
				RQ_LOCAL_PENDING);

		rv = MR_READ;
		if (bio_data_dir(req->master_bio) == WRITE)
			rv = MR_WRITE;

		get_ldev(device); /* always succeeds in this call path */
		req->w.cb = w_restart_disk_io;
		drbd_queue_work(&connection->sender_work,
				&req->w);
		break;

	case RESEND:
		/* Simply complete (local only) READs. */
		if (!(req->rq_state & RQ_WRITE) && !req->w.cb) {
			mod_rq_state(req, m, RQ_COMPLETION_SUSP, 0);
			break;
		}

		/* If RQ_NET_OK is already set, we got a P_WRITE_ACK or P_RECV_ACK
		   before the connection loss (B&C only); only P_BARRIER_ACK
		   (or the local completion?) was missing when we suspended.
		   Throwing them out of the TL here by pretending we got a BARRIER_ACK.
		   During connection handshake, we ensure that the peer was not rebooted. */
		if (!(req->rq_state & RQ_NET_OK)) {
			/* FIXME could this possibly be a req->dw.cb == w_send_out_of_sync?
			 * in that case we must not set RQ_NET_PENDING. */

			mod_rq_state(req, m, RQ_COMPLETION_SUSP, RQ_NET_QUEUED|RQ_NET_PENDING);
			if (req->w.cb) {
				/* w.cb expected to be w_send_dblock, or w_send_read_req */
				drbd_queue_work(&connection->sender_work,
						&req->w);
				rv = req->rq_state & RQ_WRITE ? MR_WRITE : MR_READ;
			} /* else: FIXME can this happen? */
			break;
		}
		/* else, fall through to BARRIER_ACKED */

	case BARRIER_ACKED:
		/* barrier ack for READ requests does not make sense */
		if (!(req->rq_state & RQ_WRITE))
			break;

		if (req->rq_state & RQ_NET_PENDING) {
			/* barrier came in before all requests were acked.
			 * this is bad, because if the connection is lost now,
			 * we won't be able to clean them up... */
			drbd_err(device, "FIXME (BARRIER_ACKED but pending)\n");
		}
		/* Allowed to complete requests, even while suspended.
		 * As this is called for all requests within a matching epoch,
		 * we need to filter, and only set RQ_NET_DONE for those that
		 * have actually been on the wire. */
		mod_rq_state(req, m, RQ_COMPLETION_SUSP,
				(req->rq_state & RQ_NET_MASK) ? RQ_NET_DONE : 0);
		break;

	case DATA_RECEIVED:
		D_ASSERT(device, req->rq_state & RQ_NET_PENDING);
		mod_rq_state(req, m, RQ_NET_PENDING, RQ_NET_OK|RQ_NET_DONE);
		break;

	case QUEUE_AS_DRBD_BARRIER:
		start_new_tl_epoch(connection);
		mod_rq_state(req, m, 0, RQ_NET_OK|RQ_NET_DONE);
		break;
	};

	return rv;
}