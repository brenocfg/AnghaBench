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
struct drbd_md {int al_stripes; int al_stripe_size_4k; } ;
struct drbd_device {int /*<<< orphan*/  al_lock; int /*<<< orphan*/  act_log; TYPE_1__* ldev; } ;
struct al_transaction_on_disk {int dummy; } ;
struct TYPE_2__ {struct drbd_md md; } ;

/* Variables and functions */
 int __al_write_transaction (struct drbd_device*,struct al_transaction_on_disk*) ; 
 int /*<<< orphan*/  lc_committed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int drbd_al_initialize(struct drbd_device *device, void *buffer)
{
	struct al_transaction_on_disk *al = buffer;
	struct drbd_md *md = &device->ldev->md;
	int al_size_4k = md->al_stripes * md->al_stripe_size_4k;
	int i;

	__al_write_transaction(device, al);
	/* There may or may not have been a pending transaction. */
	spin_lock_irq(&device->al_lock);
	lc_committed(device->act_log);
	spin_unlock_irq(&device->al_lock);

	/* The rest of the transactions will have an empty "updates" list, and
	 * are written out only to provide the context, and to initialize the
	 * on-disk ring buffer. */
	for (i = 1; i < al_size_4k; i++) {
		int err = __al_write_transaction(device, al);
		if (err)
			return err;
	}
	return 0;
}