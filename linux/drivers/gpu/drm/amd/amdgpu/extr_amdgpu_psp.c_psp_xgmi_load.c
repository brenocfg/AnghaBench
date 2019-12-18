#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  session_id; } ;
struct psp_gfx_cmd_resp {TYPE_2__ resp; } ;
struct TYPE_3__ {int initialized; int /*<<< orphan*/  session_id; int /*<<< orphan*/  xgmi_shared_mc_addr; } ;
struct psp_context {TYPE_1__ xgmi_context; int /*<<< orphan*/  fence_buf_mc_addr; int /*<<< orphan*/  ta_xgmi_ucode_size; int /*<<< orphan*/  fw_pri_mc_addr; int /*<<< orphan*/  ta_xgmi_start_addr; int /*<<< orphan*/  fw_pri_buf; int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PSP_1_MEG ; 
 int /*<<< orphan*/  PSP_XGMI_SHARED_MEM_SIZE ; 
 scalar_t__ amdgpu_sriov_vf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct psp_gfx_cmd_resp*) ; 
 struct psp_gfx_cmd_resp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int psp_cmd_submit_buf (struct psp_context*,int /*<<< orphan*/ *,struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_prep_xgmi_ta_load_cmd_buf (struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_xgmi_load(struct psp_context *psp)
{
	int ret;
	struct psp_gfx_cmd_resp *cmd;

	/*
	 * TODO: bypass the loading in sriov for now
	 */
	if (amdgpu_sriov_vf(psp->adev))
		return 0;

	cmd = kzalloc(sizeof(struct psp_gfx_cmd_resp), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	memset(psp->fw_pri_buf, 0, PSP_1_MEG);
	memcpy(psp->fw_pri_buf, psp->ta_xgmi_start_addr, psp->ta_xgmi_ucode_size);

	psp_prep_xgmi_ta_load_cmd_buf(cmd, psp->fw_pri_mc_addr,
				      psp->xgmi_context.xgmi_shared_mc_addr,
				      psp->ta_xgmi_ucode_size, PSP_XGMI_SHARED_MEM_SIZE);

	ret = psp_cmd_submit_buf(psp, NULL, cmd,
				 psp->fence_buf_mc_addr);

	if (!ret) {
		psp->xgmi_context.initialized = 1;
		psp->xgmi_context.session_id = cmd->resp.session_id;
	}

	kfree(cmd);

	return ret;
}