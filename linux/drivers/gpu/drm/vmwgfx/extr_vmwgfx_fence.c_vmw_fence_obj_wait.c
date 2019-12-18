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
struct vmw_fence_obj {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EBUSY ; 
 long dma_fence_wait_timeout (int /*<<< orphan*/ *,int,unsigned long) ; 
 scalar_t__ likely (int) ; 

int vmw_fence_obj_wait(struct vmw_fence_obj *fence, bool lazy,
		       bool interruptible, unsigned long timeout)
{
	long ret = dma_fence_wait_timeout(&fence->base, interruptible, timeout);

	if (likely(ret > 0))
		return 0;
	else if (ret == 0)
		return -EBUSY;
	else
		return ret;
}