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
struct intel_guc {int dummy; } ;
struct TYPE_2__ {int enable_guc; } ;

/* Variables and functions */
 int ENABLE_GUC_SUBMISSION ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  intel_guc_is_supported (struct intel_guc*) ; 

__attribute__((used)) static bool __guc_submission_support(struct intel_guc *guc)
{
	/* XXX: GuC submission is unavailable for now */
	return false;

	if (!intel_guc_is_supported(guc))
		return false;

	return i915_modparams.enable_guc & ENABLE_GUC_SUBMISSION;
}