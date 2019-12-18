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
 int /*<<< orphan*/  guc_disable_communication (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_is_running (struct intel_guc*) ; 
 int intel_guc_suspend (struct intel_guc*) ; 

void intel_uc_runtime_suspend(struct intel_uc *uc)
{
	struct intel_guc *guc = &uc->guc;
	int err;

	if (!intel_guc_is_running(guc))
		return;

	err = intel_guc_suspend(guc);
	if (err)
		DRM_DEBUG_DRIVER("Failed to suspend GuC, err=%d", err);

	guc_disable_communication(guc);
}