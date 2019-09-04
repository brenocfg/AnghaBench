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
struct intel_huc {struct intel_uc_fw fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_UC_FW_TYPE_HUC ; 
 int /*<<< orphan*/  huc_fw_select (struct intel_uc_fw*) ; 
 int /*<<< orphan*/  intel_uc_fw_init (struct intel_uc_fw*,int /*<<< orphan*/ ) ; 

void intel_huc_fw_init_early(struct intel_huc *huc)
{
	struct intel_uc_fw *huc_fw = &huc->fw;

	intel_uc_fw_init(huc_fw, INTEL_UC_FW_TYPE_HUC);
	huc_fw_select(huc_fw);
}