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
struct intel_uc {int /*<<< orphan*/  huc; struct intel_guc guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __uc_free_load_err_log (struct intel_uc*) ; 
 int /*<<< orphan*/  intel_guc_fini (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_huc_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uc_uses_guc (struct intel_uc*) ; 
 scalar_t__ intel_uc_uses_huc (struct intel_uc*) ; 

void intel_uc_fini(struct intel_uc *uc)
{
	struct intel_guc *guc = &uc->guc;

	if (!intel_uc_uses_guc(uc))
		return;

	if (intel_uc_uses_huc(uc))
		intel_huc_fini(&uc->huc);

	intel_guc_fini(guc);

	__uc_free_load_err_log(uc);
}