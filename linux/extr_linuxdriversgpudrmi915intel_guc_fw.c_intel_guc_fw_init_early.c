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
struct intel_uc_fw {int dummy; } ;
struct intel_guc {struct intel_uc_fw fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_UC_FW_TYPE_GUC ; 
 int /*<<< orphan*/  guc_fw_select (struct intel_uc_fw*) ; 
 int /*<<< orphan*/  intel_uc_fw_init (struct intel_uc_fw*,int /*<<< orphan*/ ) ; 

void intel_guc_fw_init_early(struct intel_guc *guc)
{
	struct intel_uc_fw *guc_fw = &guc->fw;

	intel_uc_fw_init(guc_fw, INTEL_UC_FW_TYPE_GUC);
	guc_fw_select(guc_fw);
}