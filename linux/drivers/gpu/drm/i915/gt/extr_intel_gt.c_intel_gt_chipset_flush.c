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
struct intel_gt {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_gtt_chipset_flush () ; 
 int /*<<< orphan*/  wmb () ; 

void intel_gt_chipset_flush(struct intel_gt *gt)
{
	wmb();
	if (INTEL_GEN(gt->i915) < 6)
		intel_gtt_chipset_flush();
}