#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  sector; } ;
struct drbd_request {TYPE_2__ i; TYPE_1__* master_bio; struct drbd_device* device; } ;
struct drbd_device {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int bi_opf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int) ; 
 int /*<<< orphan*/  QUEUE_AS_DRBD_BARRIER ; 
 int /*<<< orphan*/  QUEUE_FOR_NET_WRITE ; 
 int /*<<< orphan*/  QUEUE_FOR_SEND_OOS ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  TO_BE_SENT ; 
 int /*<<< orphan*/  _req_mod (struct drbd_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ drbd_set_out_of_sync (struct drbd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drbd_should_do_remote (int /*<<< orphan*/ ) ; 
 int drbd_should_send_out_of_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int drbd_process_write_request(struct drbd_request *req)
{
	struct drbd_device *device = req->device;
	int remote, send_oos;

	remote = drbd_should_do_remote(device->state);
	send_oos = drbd_should_send_out_of_sync(device->state);

	/* Need to replicate writes.  Unless it is an empty flush,
	 * which is better mapped to a DRBD P_BARRIER packet,
	 * also for drbd wire protocol compatibility reasons.
	 * If this was a flush, just start a new epoch.
	 * Unless the current epoch was empty anyways, or we are not currently
	 * replicating, in which case there is no point. */
	if (unlikely(req->i.size == 0)) {
		/* The only size==0 bios we expect are empty flushes. */
		D_ASSERT(device, req->master_bio->bi_opf & REQ_PREFLUSH);
		if (remote)
			_req_mod(req, QUEUE_AS_DRBD_BARRIER);
		return remote;
	}

	if (!remote && !send_oos)
		return 0;

	D_ASSERT(device, !(remote && send_oos));

	if (remote) {
		_req_mod(req, TO_BE_SENT);
		_req_mod(req, QUEUE_FOR_NET_WRITE);
	} else if (drbd_set_out_of_sync(device, req->i.sector, req->i.size))
		_req_mod(req, QUEUE_FOR_SEND_OOS);

	return remote;
}