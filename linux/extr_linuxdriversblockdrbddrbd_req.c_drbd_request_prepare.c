#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ size; } ;
struct drbd_request {unsigned long start_jif; int /*<<< orphan*/  in_actlog_jif; int /*<<< orphan*/  rq_state; TYPE_1__ i; int /*<<< orphan*/ * private_bio; } ;
struct drbd_device {int /*<<< orphan*/  ap_actlog_cnt; int /*<<< orphan*/  flags; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_SUSPENDED ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drbd_request* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ REQ_OP_WRITE_ZEROES ; 
 int /*<<< orphan*/  RQ_IN_ACT_LOG ; 
 int const WRITE ; 
 int /*<<< orphan*/  _drbd_start_io_acct (struct drbd_device*,struct drbd_request*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dec_ap_bio (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_al_begin_io_fastpath (struct drbd_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*) ; 
 int /*<<< orphan*/  drbd_queue_write (struct drbd_device*,struct drbd_request*) ; 
 struct drbd_request* drbd_req_new (struct drbd_device*,struct bio*) ; 
 int /*<<< orphan*/  get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drbd_request *
drbd_request_prepare(struct drbd_device *device, struct bio *bio, unsigned long start_jif)
{
	const int rw = bio_data_dir(bio);
	struct drbd_request *req;

	/* allocate outside of all locks; */
	req = drbd_req_new(device, bio);
	if (!req) {
		dec_ap_bio(device);
		/* only pass the error to the upper layers.
		 * if user cannot handle io errors, that's not our business. */
		drbd_err(device, "could not kmalloc() req\n");
		bio->bi_status = BLK_STS_RESOURCE;
		bio_endio(bio);
		return ERR_PTR(-ENOMEM);
	}
	req->start_jif = start_jif;

	if (!get_ldev(device)) {
		bio_put(req->private_bio);
		req->private_bio = NULL;
	}

	/* Update disk stats */
	_drbd_start_io_acct(device, req);

	/* process discards always from our submitter thread */
	if (bio_op(bio) == REQ_OP_WRITE_ZEROES ||
	    bio_op(bio) == REQ_OP_DISCARD)
		goto queue_for_submitter_thread;

	if (rw == WRITE && req->private_bio && req->i.size
	&& !test_bit(AL_SUSPENDED, &device->flags)) {
		if (!drbd_al_begin_io_fastpath(device, &req->i))
			goto queue_for_submitter_thread;
		req->rq_state |= RQ_IN_ACT_LOG;
		req->in_actlog_jif = jiffies;
	}
	return req;

 queue_for_submitter_thread:
	atomic_inc(&device->ap_actlog_cnt);
	drbd_queue_write(device, req);
	return NULL;
}