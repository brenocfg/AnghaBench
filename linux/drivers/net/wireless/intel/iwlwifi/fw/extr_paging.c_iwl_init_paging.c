#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_fw_runtime {TYPE_3__* trans; TYPE_1__* fw; } ;
struct fw_img {int /*<<< orphan*/  paging_mem_size; } ;
typedef  enum iwl_ucode_type { ____Placeholder_iwl_ucode_type } iwl_ucode_type ;
struct TYPE_6__ {TYPE_2__* trans_cfg; } ;
struct TYPE_5__ {scalar_t__ gen2; } ;
struct TYPE_4__ {struct fw_img* img; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_fw_runtime*,char*) ; 
 int /*<<< orphan*/  iwl_free_fw_paging (struct iwl_fw_runtime*) ; 
 int iwl_save_fw_paging (struct iwl_fw_runtime*,struct fw_img const*) ; 
 int iwl_send_paging_cmd (struct iwl_fw_runtime*,struct fw_img const*) ; 

int iwl_init_paging(struct iwl_fw_runtime *fwrt, enum iwl_ucode_type type)
{
	const struct fw_img *fw = &fwrt->fw->img[type];
	int ret;

	if (fwrt->trans->trans_cfg->gen2)
		return 0;

	/*
	 * Configure and operate fw paging mechanism.
	 * The driver configures the paging flow only once.
	 * The CPU2 paging image is included in the IWL_UCODE_INIT image.
	 */
	if (!fw->paging_mem_size)
		return 0;

	ret = iwl_save_fw_paging(fwrt, fw);
	if (ret) {
		IWL_ERR(fwrt, "failed to save the FW paging image\n");
		return ret;
	}

	ret = iwl_send_paging_cmd(fwrt, fw);
	if (ret) {
		IWL_ERR(fwrt, "failed to send the paging cmd\n");
		iwl_free_fw_paging(fwrt);
		return ret;
	}

	return 0;
}