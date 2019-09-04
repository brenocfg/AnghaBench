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
struct lc_element {scalar_t__ lc_number; } ;
struct drbd_device {int /*<<< orphan*/  al_wait; TYPE_1__* act_log; } ;
struct TYPE_2__ {int nr_elements; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ LC_FREE ; 
 int /*<<< orphan*/  __LC_LOCKED ; 
 int /*<<< orphan*/  _try_lc_del (struct drbd_device*,struct lc_element*) ; 
 struct lc_element* lc_element_by_index (TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void drbd_al_shrink(struct drbd_device *device)
{
	struct lc_element *al_ext;
	int i;

	D_ASSERT(device, test_bit(__LC_LOCKED, &device->act_log->flags));

	for (i = 0; i < device->act_log->nr_elements; i++) {
		al_ext = lc_element_by_index(device->act_log, i);
		if (al_ext->lc_number == LC_FREE)
			continue;
		wait_event(device->al_wait, _try_lc_del(device, al_ext));
	}

	wake_up(&device->al_wait);
}