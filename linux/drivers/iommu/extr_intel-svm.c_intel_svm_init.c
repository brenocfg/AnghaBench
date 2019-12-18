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
struct intel_iommu {int /*<<< orphan*/  cap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  X86_FEATURE_GBPAGES ; 
 int /*<<< orphan*/  X86_FEATURE_LA57 ; 
 int /*<<< orphan*/  cap_5lp_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_fl1gp_support (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_feature_enabled (int /*<<< orphan*/ ) ; 

int intel_svm_init(struct intel_iommu *iommu)
{
	if (cpu_feature_enabled(X86_FEATURE_GBPAGES) &&
			!cap_fl1gp_support(iommu->cap))
		return -EINVAL;

	if (cpu_feature_enabled(X86_FEATURE_LA57) &&
			!cap_5lp_support(iommu->cap))
		return -EINVAL;

	return 0;
}