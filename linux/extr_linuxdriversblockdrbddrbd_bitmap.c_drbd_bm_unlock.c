#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drbd_device {struct drbd_bitmap* bitmap; } ;
struct drbd_bitmap {int bm_flags; int /*<<< orphan*/  bm_change; int /*<<< orphan*/ * bm_task; int /*<<< orphan*/ * bm_why; } ;

/* Variables and functions */
 int BM_LOCKED_MASK ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drbd_bm_unlock(struct drbd_device *device)
{
	struct drbd_bitmap *b = device->bitmap;
	if (!b) {
		drbd_err(device, "FIXME no bitmap in drbd_bm_unlock!?\n");
		return;
	}

	if (!(BM_LOCKED_MASK & device->bitmap->bm_flags))
		drbd_err(device, "FIXME bitmap not locked in bm_unlock\n");

	b->bm_flags &= ~BM_LOCKED_MASK;
	b->bm_why  = NULL;
	b->bm_task = NULL;
	mutex_unlock(&b->bm_change);
}