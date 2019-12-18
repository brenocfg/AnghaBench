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
typedef  int /*<<< orphan*/  uint32_t ;
struct psp_gfx_cmd_resp {int dummy; } ;
struct psp_context {TYPE_2__* cmd_buf_mem; int /*<<< orphan*/  fence_buf_mc_addr; int /*<<< orphan*/  toc_bin_size; int /*<<< orphan*/  fw_pri_mc_addr; int /*<<< orphan*/  toc_start_addr; int /*<<< orphan*/  fw_pri_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  tmr_size; } ;
struct TYPE_4__ {TYPE_1__ resp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PSP_1_MEG ; 
 int /*<<< orphan*/  kfree (struct psp_gfx_cmd_resp*) ; 
 struct psp_gfx_cmd_resp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int psp_cmd_submit_buf (struct psp_context*,int /*<<< orphan*/ *,struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_prep_load_toc_cmd_buf (struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_load_toc(struct psp_context *psp,
			uint32_t *tmr_size)
{
	int ret;
	struct psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(sizeof(struct psp_gfx_cmd_resp), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;
	/* Copy toc to psp firmware private buffer */
	memset(psp->fw_pri_buf, 0, PSP_1_MEG);
	memcpy(psp->fw_pri_buf, psp->toc_start_addr, psp->toc_bin_size);

	psp_prep_load_toc_cmd_buf(cmd, psp->fw_pri_mc_addr, psp->toc_bin_size);

	ret = psp_cmd_submit_buf(psp, NULL, cmd,
				 psp->fence_buf_mc_addr);
	if (!ret)
		*tmr_size = psp->cmd_buf_mem->resp.tmr_size;
	kfree(cmd);
	return ret;
}