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
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {TYPE_1__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  dma_resv_add_excl_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dma_resv_test_signaled_rcu (int /*<<< orphan*/ ,int) ; 
 long dma_resv_wait_timeout_rcu (int /*<<< orphan*/ ,int,int,long) ; 

int ttm_bo_wait(struct ttm_buffer_object *bo,
		bool interruptible, bool no_wait)
{
	long timeout = 15 * HZ;

	if (no_wait) {
		if (dma_resv_test_signaled_rcu(bo->base.resv, true))
			return 0;
		else
			return -EBUSY;
	}

	timeout = dma_resv_wait_timeout_rcu(bo->base.resv, true,
						      interruptible, timeout);
	if (timeout < 0)
		return timeout;

	if (timeout == 0)
		return -EBUSY;

	dma_resv_add_excl_fence(bo->base.resv, NULL);
	return 0;
}