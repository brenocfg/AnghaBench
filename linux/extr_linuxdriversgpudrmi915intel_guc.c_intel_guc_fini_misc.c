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
struct intel_guc {int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  guc_fini_wq (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_uc_fw_fini (int /*<<< orphan*/ *) ; 

void intel_guc_fini_misc(struct intel_guc *guc)
{
	intel_uc_fw_fini(&guc->fw);
	guc_fini_wq(guc);
}