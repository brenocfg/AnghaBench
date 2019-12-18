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
struct intel_uc {struct intel_guc guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int guc_communication_enabled (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_enable_communication (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_is_running (struct intel_guc*) ; 
 int intel_guc_resume (struct intel_guc*) ; 

__attribute__((used)) static int __uc_resume(struct intel_uc *uc, bool enable_communication)
{
	struct intel_guc *guc = &uc->guc;
	int err;

	if (!intel_guc_is_running(guc))
		return 0;

	/* Make sure we enable communication if and only if it's disabled */
	GEM_BUG_ON(enable_communication == guc_communication_enabled(guc));

	if (enable_communication)
		guc_enable_communication(guc);

	err = intel_guc_resume(guc);
	if (err) {
		DRM_DEBUG_DRIVER("Failed to resume GuC, err=%d", err);
		return err;
	}

	return 0;
}