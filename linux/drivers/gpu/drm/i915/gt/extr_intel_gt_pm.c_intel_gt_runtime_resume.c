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
struct intel_gt {int /*<<< orphan*/  uc; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_gt_init_swizzling (struct intel_gt*) ; 
 int intel_uc_runtime_resume (int /*<<< orphan*/ *) ; 

int intel_gt_runtime_resume(struct intel_gt *gt)
{
	intel_gt_init_swizzling(gt);

	return intel_uc_runtime_resume(&gt->uc);
}