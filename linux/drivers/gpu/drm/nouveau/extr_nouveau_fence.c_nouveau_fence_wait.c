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
struct nouveau_fence {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EBUSY ; 
 int HZ ; 
 long dma_fence_wait_timeout (int /*<<< orphan*/ *,int,int) ; 
 int nouveau_fence_wait_busy (struct nouveau_fence*,int) ; 

int
nouveau_fence_wait(struct nouveau_fence *fence, bool lazy, bool intr)
{
	long ret;

	if (!lazy)
		return nouveau_fence_wait_busy(fence, intr);

	ret = dma_fence_wait_timeout(&fence->base, intr, 15 * HZ);
	if (ret < 0)
		return ret;
	else if (!ret)
		return -EBUSY;
	else
		return 0;
}