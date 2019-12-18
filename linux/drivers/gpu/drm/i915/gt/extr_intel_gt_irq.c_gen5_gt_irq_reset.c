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
struct intel_uncore {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  i915; struct intel_uncore* uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN3_IRQ_RESET (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN6_PM ; 
 int /*<<< orphan*/  GT ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 

void gen5_gt_irq_reset(struct intel_gt *gt)
{
	struct intel_uncore *uncore = gt->uncore;

	GEN3_IRQ_RESET(uncore, GT);
	if (INTEL_GEN(gt->i915) >= 6)
		GEN3_IRQ_RESET(uncore, GEN6_PM);
}