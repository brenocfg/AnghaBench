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
struct psp_context {int /*<<< orphan*/  fence_buf_mc_addr; int /*<<< orphan*/  tmr_mc_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct psp_gfx_cmd_resp*) ; 
 struct psp_gfx_cmd_resp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int psp_cmd_submit_buf (struct psp_context*,int /*<<< orphan*/ *,struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psp_prep_tmr_cmd_buf (struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int psp_tmr_load(struct psp_context *psp)
{
	int ret;
	struct psp_gfx_cmd_resp *cmd;

	cmd = kzalloc(sizeof(struct psp_gfx_cmd_resp), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	psp_prep_tmr_cmd_buf(cmd, psp->tmr_mc_addr, 0x300000);

	ret = psp_cmd_submit_buf(psp, NULL, cmd,
				 psp->fence_buf_mc_addr, 1);
	if (ret)
		goto failed;

	kfree(cmd);

	return 0;

failed:
	kfree(cmd);
	return ret;
}