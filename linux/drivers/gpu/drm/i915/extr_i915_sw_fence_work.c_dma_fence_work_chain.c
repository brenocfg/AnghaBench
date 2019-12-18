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
struct dma_fence_work {int /*<<< orphan*/  cb; int /*<<< orphan*/  chain; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int __i915_sw_fence_await_dma_fence (int /*<<< orphan*/ *,struct dma_fence*,int /*<<< orphan*/ *) ; 

int dma_fence_work_chain(struct dma_fence_work *f, struct dma_fence *signal)
{
	if (!signal)
		return 0;

	return __i915_sw_fence_await_dma_fence(&f->chain, signal, &f->cb);
}