#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct psp_gfx_cmd_resp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  session_id; } ;
struct psp_context {int /*<<< orphan*/  fence_buf_mc_addr; TYPE_1__ ras; int /*<<< orphan*/  adev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ amdgpu_sriov_vf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct psp_gfx_cmd_resp*) ; 
 struct psp_gfx_cmd_resp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int psp_cmd_submit_buf (struct psp_context*,int /*<<< orphan*/ *,struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_prep_ras_ta_invoke_cmd_buf (struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int psp_ras_invoke(struct psp_context *psp, uint32_t ta_cmd_id)
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

	psp_prep_ras_ta_invoke_cmd_buf(cmd, ta_cmd_id,
			psp->ras.session_id);

	ret = psp_cmd_submit_buf(psp, NULL, cmd,
			psp->fence_buf_mc_addr);

	kfree(cmd);

	return ret;
}