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
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
vmw_fence_obj_unreference(struct vmw_fence_obj **fence_p)
{
	struct vmw_fence_obj *fence = *fence_p;

	*fence_p = NULL;
	if (fence)
		dma_fence_put(&fence->base);
}