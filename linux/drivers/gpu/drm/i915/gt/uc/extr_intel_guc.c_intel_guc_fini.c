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
struct intel_guc {int /*<<< orphan*/  fw; int /*<<< orphan*/  log; int /*<<< orphan*/  ct; } ;
struct intel_gt {int /*<<< orphan*/  ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  guc_shared_data_destroy (struct intel_guc*) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int /*<<< orphan*/  i915_ggtt_disable_guc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_guc_ads_destroy (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_ct_fini (int /*<<< orphan*/ *) ; 
 scalar_t__ intel_guc_is_submission_supported (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_log_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_guc_submission_fini (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_uc_fw_cleanup_fetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fw_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_fw_is_available (int /*<<< orphan*/ *) ; 

void intel_guc_fini(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);

	if (!intel_uc_fw_is_available(&guc->fw))
		return;

	i915_ggtt_disable_guc(gt->ggtt);

	if (intel_guc_is_submission_supported(guc))
		intel_guc_submission_fini(guc);

	intel_guc_ct_fini(&guc->ct);

	intel_guc_ads_destroy(guc);
	intel_guc_log_destroy(&guc->log);
	guc_shared_data_destroy(guc);
	intel_uc_fw_fini(&guc->fw);
	intel_uc_fw_cleanup_fetch(&guc->fw);
}