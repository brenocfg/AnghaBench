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
struct intel_gt {struct intel_uncore* uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_IRQ_RESET_NDX (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GT ; 

void gen8_gt_irq_reset(struct intel_gt *gt)
{
	struct intel_uncore *uncore = gt->uncore;

	GEN8_IRQ_RESET_NDX(uncore, GT, 0);
	GEN8_IRQ_RESET_NDX(uncore, GT, 1);
	GEN8_IRQ_RESET_NDX(uncore, GT, 2);
	GEN8_IRQ_RESET_NDX(uncore, GT, 3);
}