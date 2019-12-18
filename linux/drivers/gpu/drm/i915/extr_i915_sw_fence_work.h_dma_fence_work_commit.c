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
struct dma_fence_work {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_sw_fence_commit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dma_fence_work_commit(struct dma_fence_work *f)
{
	i915_sw_fence_commit(&f->chain);
}