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
struct iwl_trans {int dummy; } ;
struct fw_img {scalar_t__ is_dual_cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_FW (struct iwl_trans*,char*,char*) ; 
 int /*<<< orphan*/  IWL_DEBUG_POWER (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELEASE_CPU_RESET ; 
 int RELEASE_CPU_RESET_BIT ; 
 int /*<<< orphan*/  WFPM_GP2 ; 
 int /*<<< orphan*/  iwl_pcie_apply_destination (struct iwl_trans*) ; 
 scalar_t__ iwl_pcie_dbg_on (struct iwl_trans*) ; 
 int iwl_pcie_load_cpu_sections_8000 (struct iwl_trans*,struct fw_img const*,int,int*) ; 
 int /*<<< orphan*/  iwl_read_prph (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_write_prph (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_pcie_load_given_ucode_8000(struct iwl_trans *trans,
					  const struct fw_img *image)
{
	int ret = 0;
	int first_ucode_section;

	IWL_DEBUG_FW(trans, "working with %s CPU\n",
		     image->is_dual_cpus ? "Dual" : "Single");

	if (iwl_pcie_dbg_on(trans))
		iwl_pcie_apply_destination(trans);

	IWL_DEBUG_POWER(trans, "Original WFPM value = 0x%08X\n",
			iwl_read_prph(trans, WFPM_GP2));

	/*
	 * Set default value. On resume reading the values that were
	 * zeored can provide debug data on the resume flow.
	 * This is for debugging only and has no functional impact.
	 */
	iwl_write_prph(trans, WFPM_GP2, 0x01010101);

	/* configure the ucode to be ready to get the secured image */
	/* release CPU reset */
	iwl_write_prph(trans, RELEASE_CPU_RESET, RELEASE_CPU_RESET_BIT);

	/* load to FW the binary Secured sections of CPU1 */
	ret = iwl_pcie_load_cpu_sections_8000(trans, image, 1,
					      &first_ucode_section);
	if (ret)
		return ret;

	/* load to FW the binary sections of CPU2 */
	return iwl_pcie_load_cpu_sections_8000(trans, image, 2,
					       &first_ucode_section);
}