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
typedef  int uint32_t ;
struct psp_context {int fw_pri_mc_addr; int /*<<< orphan*/  sys_bin_size; int /*<<< orphan*/  sys_start_addr; int /*<<< orphan*/  fw_pri_buf; void* sos_fw_version; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP0 ; 
 int /*<<< orphan*/  PSP_1_MEG ; 
 void* RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_35 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_36 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_58 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_81 ; 
 int /*<<< orphan*/  printk (char*,void*) ; 
 int psp_wait_for (struct psp_context*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int psp_v12_0_bootloader_load_sysdrv(struct psp_context *psp)
{
	int ret;
	uint32_t psp_gfxdrv_command_reg = 0;
	struct amdgpu_device *adev = psp->adev;
	uint32_t sol_reg;

	/* Check sOS sign of life register to confirm sys driver and sOS
	 * are already been loaded.
	 */
	sol_reg = RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81);
	if (sol_reg) {
		psp->sos_fw_version = RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_58);
		printk("sos fw version = 0x%x.\n", psp->sos_fw_version);
		return 0;
	}

	/* Wait for bootloader to signify that is ready having bit 31 of C2PMSG_35 set to 1 */
	ret = psp_wait_for(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
			   0x80000000, 0x80000000, false);
	if (ret)
		return ret;

	memset(psp->fw_pri_buf, 0, PSP_1_MEG);

	/* Copy PSP System Driver binary to memory */
	memcpy(psp->fw_pri_buf, psp->sys_start_addr, psp->sys_bin_size);

	/* Provide the sys driver to bootloader */
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36,
	       (uint32_t)(psp->fw_pri_mc_addr >> 20));
	psp_gfxdrv_command_reg = 1 << 16;
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35,
	       psp_gfxdrv_command_reg);

	/* there might be handshake issue with hardware which needs delay */
	mdelay(20);

	ret = psp_wait_for(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
			   0x80000000, 0x80000000, false);

	return ret;
}