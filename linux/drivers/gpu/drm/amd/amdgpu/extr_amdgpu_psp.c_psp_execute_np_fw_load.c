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
struct psp_context {int /*<<< orphan*/  fence_buf_mc_addr; int /*<<< orphan*/  cmd; } ;
struct amdgpu_firmware_info {int dummy; } ;

/* Variables and functions */
 int psp_cmd_submit_buf (struct psp_context*,struct amdgpu_firmware_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int psp_prep_load_ip_fw_cmd_buf (struct amdgpu_firmware_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_execute_np_fw_load(struct psp_context *psp,
			       struct amdgpu_firmware_info *ucode)
{
	int ret = 0;

	ret = psp_prep_load_ip_fw_cmd_buf(ucode, psp->cmd);
	if (ret)
		return ret;

	ret = psp_cmd_submit_buf(psp, ucode, psp->cmd,
				 psp->fence_buf_mc_addr);

	return ret;
}