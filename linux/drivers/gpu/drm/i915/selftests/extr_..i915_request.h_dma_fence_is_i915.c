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
struct dma_fence {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_fence_ops ; 

__attribute__((used)) static inline bool dma_fence_is_i915(const struct dma_fence *fence)
{
	return fence->ops == &i915_fence_ops;
}