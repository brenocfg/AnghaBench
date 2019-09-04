#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  backing_dev_info; } ;
struct drbd_device {char congestion_reason; TYPE_1__* ldev; } ;
struct TYPE_6__ {TYPE_2__* connection; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  backing_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_PENDING ; 
 int /*<<< orphan*/  D_UP_TO_DATE ; 
 int /*<<< orphan*/  NET_CONGESTED ; 
 int WB_async_congested ; 
 int WB_sync_congested ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int bdi_congested (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* first_peer_device (struct drbd_device*) ; 
 scalar_t__ get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  get_ldev_if_state (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  may_inc_ap_bio (struct drbd_device*) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drbd_congested(void *congested_data, int bdi_bits)
{
	struct drbd_device *device = congested_data;
	struct request_queue *q;
	char reason = '-';
	int r = 0;

	if (!may_inc_ap_bio(device)) {
		/* DRBD has frozen IO */
		r = bdi_bits;
		reason = 'd';
		goto out;
	}

	if (test_bit(CALLBACK_PENDING, &first_peer_device(device)->connection->flags)) {
		r |= (1 << WB_async_congested);
		/* Without good local data, we would need to read from remote,
		 * and that would need the worker thread as well, which is
		 * currently blocked waiting for that usermode helper to
		 * finish.
		 */
		if (!get_ldev_if_state(device, D_UP_TO_DATE))
			r |= (1 << WB_sync_congested);
		else
			put_ldev(device);
		r &= bdi_bits;
		reason = 'c';
		goto out;
	}

	if (get_ldev(device)) {
		q = bdev_get_queue(device->ldev->backing_bdev);
		r = bdi_congested(q->backing_dev_info, bdi_bits);
		put_ldev(device);
		if (r)
			reason = 'b';
	}

	if (bdi_bits & (1 << WB_async_congested) &&
	    test_bit(NET_CONGESTED, &first_peer_device(device)->connection->flags)) {
		r |= (1 << WB_async_congested);
		reason = reason == 'b' ? 'a' : 'n';
	}

out:
	device->congestion_reason = reason;
	return r;
}