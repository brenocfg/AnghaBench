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
struct intel_guc {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_GUC_HOST_INTERRUPT ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_uncore_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen11_guc_raise_irq(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);

	intel_uncore_write(gt->uncore, GEN11_GUC_HOST_INTERRUPT, 0);
}