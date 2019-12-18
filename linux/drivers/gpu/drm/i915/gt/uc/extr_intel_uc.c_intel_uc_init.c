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
struct intel_huc {int /*<<< orphan*/  fw; } ;
struct intel_guc {int dummy; } ;
struct intel_uc {struct intel_huc huc; struct intel_guc guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int intel_guc_init (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_huc_init (struct intel_huc*) ; 
 int /*<<< orphan*/  intel_uc_fw_cleanup_fetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_supports_guc_submission (struct intel_uc*) ; 
 int /*<<< orphan*/  intel_uc_uses_guc (struct intel_uc*) ; 
 scalar_t__ intel_uc_uses_huc (struct intel_uc*) ; 

void intel_uc_init(struct intel_uc *uc)
{
	struct intel_guc *guc = &uc->guc;
	struct intel_huc *huc = &uc->huc;
	int ret;

	if (!intel_uc_uses_guc(uc))
		return;

	/* XXX: GuC submission is unavailable for now */
	GEM_BUG_ON(intel_uc_supports_guc_submission(uc));

	ret = intel_guc_init(guc);
	if (ret) {
		intel_uc_fw_cleanup_fetch(&huc->fw);
		return;
	}

	if (intel_uc_uses_huc(uc))
		intel_huc_init(huc);
}