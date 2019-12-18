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
struct intel_gt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_gt_is_wedged (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_reset (struct intel_gt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_set_wedged (struct intel_gt*) ; 

bool igt_force_reset(struct intel_gt *gt)
{
	intel_gt_set_wedged(gt);
	intel_gt_reset(gt, 0, NULL);

	return !intel_gt_is_wedged(gt);
}