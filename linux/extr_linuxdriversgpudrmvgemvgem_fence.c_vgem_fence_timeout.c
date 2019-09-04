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
struct vgem_fence {int /*<<< orphan*/  base; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_signal (int /*<<< orphan*/ *) ; 
 struct vgem_fence* fence ; 
 struct vgem_fence* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void vgem_fence_timeout(struct timer_list *t)
{
	struct vgem_fence *fence = from_timer(fence, t, timer);

	dma_fence_signal(&fence->base);
}