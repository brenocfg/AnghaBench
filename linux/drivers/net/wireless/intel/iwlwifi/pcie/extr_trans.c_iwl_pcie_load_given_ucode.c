#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* fw_mon; } ;
struct iwl_trans {TYPE_3__ dbg; TYPE_1__* trans_cfg; } ;
struct fw_img {scalar_t__ is_dual_cpus; } ;
struct TYPE_8__ {scalar_t__ fw_monitor; } ;
struct TYPE_6__ {int size; int physical; } ;
struct TYPE_5__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_RESET ; 
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_trans*,char*,char*) ; 
 scalar_t__ IWL_DEVICE_FAMILY_7000 ; 
 int LMPM_SECURE_CPU2_HDR_MEM_SPACE ; 
 int /*<<< orphan*/  LMPM_SECURE_UCODE_LOAD_CPU2_HDR_ADDR ; 
 int /*<<< orphan*/  MON_BUFF_BASE_ADDR ; 
 int /*<<< orphan*/  MON_BUFF_END_ADDR ; 
 int /*<<< orphan*/  iwl_enable_interrupts (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_alloc_fw_monitor (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_apply_destination (struct iwl_trans*) ; 
 scalar_t__ iwl_pcie_dbg_on (struct iwl_trans*) ; 
 int iwl_pcie_load_cpu_sections (struct iwl_trans*,struct fw_img const*,int,int*) ; 
 int /*<<< orphan*/  iwl_write32 (struct iwl_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ iwlwifi_mod_params ; 

__attribute__((used)) static int iwl_pcie_load_given_ucode(struct iwl_trans *trans,
				const struct fw_img *image)
{
	int ret = 0;
	int first_ucode_section;

	IWL_DEBUG_FW(trans, "working with %s CPU\n",
		     image->is_dual_cpus ? "Dual" : "Single");

	/* load to FW the binary non secured sections of CPU1 */
	ret = iwl_pcie_load_cpu_sections(trans, image, 1, &first_ucode_section);
	if (ret)
		return ret;

	if (image->is_dual_cpus) {
		/* set CPU2 header address */
		iwl_write_prph(trans,
			       LMPM_SECURE_UCODE_LOAD_CPU2_HDR_ADDR,
			       LMPM_SECURE_CPU2_HDR_MEM_SPACE);

		/* load to FW the binary sections of CPU2 */
		ret = iwl_pcie_load_cpu_sections(trans, image, 2,
						 &first_ucode_section);
		if (ret)
			return ret;
	}

	/* supported for 7000 only for the moment */
	if (iwlwifi_mod_params.fw_monitor &&
	    trans->trans_cfg->device_family == IWL_DEVICE_FAMILY_7000) {
		iwl_pcie_alloc_fw_monitor(trans, 0);

		if (trans->dbg.fw_mon[0].size) {
			iwl_write_prph(trans, MON_BUFF_BASE_ADDR,
				       trans->dbg.fw_mon[0].physical >> 4);
			iwl_write_prph(trans, MON_BUFF_END_ADDR,
				       (trans->dbg.fw_mon[0].physical +
					trans->dbg.fw_mon[0].size) >> 4);
		}
	} else if (iwl_pcie_dbg_on(trans)) {
		iwl_pcie_apply_destination(trans);
	}

	iwl_enable_interrupts(trans);

	/* release CPU reset */
	iwl_write32(trans, CSR_RESET, 0);

	return 0;
}