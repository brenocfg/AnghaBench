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
struct intel_gt {TYPE_1__* ggtt; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_OBJECT_NEEDS_FENCE ; 
 int __igt_reset_evict_vma (struct intel_gt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evict_fence ; 

__attribute__((used)) static int igt_reset_evict_fence(void *arg)
{
	struct intel_gt *gt = arg;

	return __igt_reset_evict_vma(gt, &gt->ggtt->vm,
				     evict_fence, EXEC_OBJECT_NEEDS_FENCE);
}