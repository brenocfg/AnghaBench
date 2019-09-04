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
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_enable_sw_signaling (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 

__attribute__((used)) static bool drm_syncobj_null_fence_enable_signaling(struct dma_fence *fence)
{
    dma_fence_enable_sw_signaling(fence);
    return !dma_fence_is_signaled(fence);
}