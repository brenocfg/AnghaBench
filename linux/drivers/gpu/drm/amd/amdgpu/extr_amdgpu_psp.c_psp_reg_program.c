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
typedef  int /*<<< orphan*/  uint32_t ;
struct psp_gfx_cmd_resp {int dummy; } ;
struct psp_context {int /*<<< orphan*/  fence_buf_mc_addr; } ;
typedef  enum psp_reg_prog_id { ____Placeholder_psp_reg_prog_id } psp_reg_prog_id ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PSP_REG_LAST ; 
 int /*<<< orphan*/  kfree (struct psp_gfx_cmd_resp*) ; 
 struct psp_gfx_cmd_resp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int psp_cmd_submit_buf (struct psp_context*,int /*<<< orphan*/ *,struct psp_gfx_cmd_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psp_prep_reg_prog_cmd_buf (struct psp_gfx_cmd_resp*,int,int /*<<< orphan*/ ) ; 

int psp_reg_program(struct psp_context *psp, enum psp_reg_prog_id reg,
		uint32_t value)
{
	struct psp_gfx_cmd_resp *cmd = NULL;
	int ret = 0;

	if (reg >= PSP_REG_LAST)
		return -EINVAL;

	cmd = kzalloc(sizeof(struct psp_gfx_cmd_resp), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	psp_prep_reg_prog_cmd_buf(cmd, reg, value);
	ret = psp_cmd_submit_buf(psp, NULL, cmd, psp->fence_buf_mc_addr);

	kfree(cmd);
	return ret;
}