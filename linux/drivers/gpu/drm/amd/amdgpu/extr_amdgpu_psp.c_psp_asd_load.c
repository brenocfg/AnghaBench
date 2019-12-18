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
struct psp_gfx_cmd_resp {int dummy; } ;
struct psp_context {int /*<<< orphan*/  fence_buf_mc_addr; int /*<<< orphan*/  asd_ucode_size; int /*<<< orphan*/  asd_shared_mc_addr; int /*<<< orphan*/  fw_pri_mc_addr; int /*<<< orphan*/  asd_start_addr; int /*<<< orphan*/  fw_pri_buf; int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PSP_1_MEG ; 
 int /*<<< orphan*/  PSP_ASD_SHARED_MEM_SIZE ; 
 scalar_t__ amdgpu_sriov_vf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct psp_gfx_cmd_resp*) ; 
 struct psp_gfx_cmd_resp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int psp_cmd_submit_buf (struct psp_context*,int /*<<< orphan*/ *,struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_prep_asd_cmd_buf (struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_asd_load(struct psp_context *psp)
{
	int ret;
	struct psp_gfx_cmd_resp *cmd;

	/* If PSP version doesn't match ASD version, asd loading will be failed.
	 * add workaround to bypass it for sriov now.
	 * TODO: add version check to make it common
	 */
	if (amdgpu_sriov_vf(psp->adev))
		return 0;

	cmd = kzalloc(sizeof(struct psp_gfx_cmd_resp), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	memset(psp->fw_pri_buf, 0, PSP_1_MEG);
	memcpy(psp->fw_pri_buf, psp->asd_start_addr, psp->asd_ucode_size);

	psp_prep_asd_cmd_buf(cmd, psp->fw_pri_mc_addr, psp->asd_shared_mc_addr,
			     psp->asd_ucode_size, PSP_ASD_SHARED_MEM_SIZE);

	ret = psp_cmd_submit_buf(psp, NULL, cmd,
				 psp->fence_buf_mc_addr);

	kfree(cmd);

	return ret;
}