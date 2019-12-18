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
typedef  int /*<<< orphan*/  u32 ;
struct intel_gt {int /*<<< orphan*/  uncore; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEN11_GRDOM_GUC ; 
 int /*<<< orphan*/  GEN9_GRDOM_GUC ; 
 int /*<<< orphan*/  HAS_GT_UC (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int gen6_hw_domain_reset (struct intel_gt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int intel_reset_guc(struct intel_gt *gt)
{
	u32 guc_domain =
		INTEL_GEN(gt->i915) >= 11 ? GEN11_GRDOM_GUC : GEN9_GRDOM_GUC;
	int ret;

	GEM_BUG_ON(!HAS_GT_UC(gt->i915));

	intel_uncore_forcewake_get(gt->uncore, FORCEWAKE_ALL);
	ret = gen6_hw_domain_reset(gt, guc_domain);
	intel_uncore_forcewake_put(gt->uncore, FORCEWAKE_ALL);

	return ret;
}