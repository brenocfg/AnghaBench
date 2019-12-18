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
struct intel_gt {int /*<<< orphan*/  i915; } ;
struct TYPE_2__ {scalar_t__ gpu_reset_clobbers_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 TYPE_1__* INTEL_INFO (int /*<<< orphan*/ ) ; 
 scalar_t__ __intel_gt_reset (struct intel_gt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool reset_engines(struct intel_gt *gt)
{
	if (INTEL_INFO(gt->i915)->gpu_reset_clobbers_display)
		return false;

	return __intel_gt_reset(gt, ALL_ENGINES) == 0;
}