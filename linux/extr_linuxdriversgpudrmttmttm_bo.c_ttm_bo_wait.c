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
struct ttm_buffer_object {int /*<<< orphan*/  resv; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  reservation_object_add_excl_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ reservation_object_test_signaled_rcu (int /*<<< orphan*/ ,int) ; 
 long reservation_object_wait_timeout_rcu (int /*<<< orphan*/ ,int,int,long) ; 

int ttm_bo_wait(struct ttm_buffer_object *bo,
		bool interruptible, bool no_wait)
{
	long timeout = 15 * HZ;

	if (no_wait) {
		if (reservation_object_test_signaled_rcu(bo->resv, true))
			return 0;
		else
			return -EBUSY;
	}

	timeout = reservation_object_wait_timeout_rcu(bo->resv, true,
						      interruptible, timeout);
	if (timeout < 0)
		return timeout;

	if (timeout == 0)
		return -EBUSY;

	reservation_object_add_excl_fence(bo->resv, NULL);
	return 0;
}