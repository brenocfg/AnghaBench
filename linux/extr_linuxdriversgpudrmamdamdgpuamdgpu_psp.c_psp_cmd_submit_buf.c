#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct psp_gfx_cmd_resp {int dummy; } ;
struct psp_context {TYPE_2__* cmd_buf_mem; scalar_t__ fence_buf; int /*<<< orphan*/  cmd_buf_mc_addr; } ;
struct amdgpu_firmware_info {int /*<<< orphan*/  tmr_mc_addr_hi; int /*<<< orphan*/  tmr_mc_addr_lo; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw_addr_hi; int /*<<< orphan*/  fw_addr_lo; } ;
struct TYPE_5__ {TYPE_1__ resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSP_CMD_BUFFER_SIZE ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct psp_gfx_cmd_resp*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int psp_cmd_submit (struct psp_context*,struct amdgpu_firmware_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
psp_cmd_submit_buf(struct psp_context *psp,
		   struct amdgpu_firmware_info *ucode,
		   struct psp_gfx_cmd_resp *cmd, uint64_t fence_mc_addr,
		   int index)
{
	int ret;

	memset(psp->cmd_buf_mem, 0, PSP_CMD_BUFFER_SIZE);

	memcpy(psp->cmd_buf_mem, cmd, sizeof(struct psp_gfx_cmd_resp));

	ret = psp_cmd_submit(psp, ucode, psp->cmd_buf_mc_addr,
			     fence_mc_addr, index);

	while (*((unsigned int *)psp->fence_buf) != index) {
		msleep(1);
	}

	if (ucode) {
		ucode->tmr_mc_addr_lo = psp->cmd_buf_mem->resp.fw_addr_lo;
		ucode->tmr_mc_addr_hi = psp->cmd_buf_mem->resp.fw_addr_hi;
	}

	return ret;
}