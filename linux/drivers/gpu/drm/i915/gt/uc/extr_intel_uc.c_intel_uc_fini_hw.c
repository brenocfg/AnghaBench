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
 int /*<<< orphan*/  __uc_sanitize (struct intel_uc*) ; 
 int /*<<< orphan*/  guc_disable_communication (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_is_running (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_submission_disable (struct intel_guc*) ; 
 scalar_t__ intel_uc_supports_guc_submission (struct intel_uc*) ; 

void intel_uc_fini_hw(struct intel_uc *uc)
{
	struct intel_guc *guc = &uc->guc;

	if (!intel_guc_is_running(guc))
		return;

	if (intel_uc_supports_guc_submission(uc))
		intel_guc_submission_disable(guc);

	guc_disable_communication(guc);
	__uc_sanitize(uc);
}