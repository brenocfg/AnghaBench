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
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA53_RESET ; 
 int /*<<< orphan*/  CPU_BOOT_STATUS_NA ; 
 int /*<<< orphan*/  CPU_RESET_ASSERT ; 
 int /*<<< orphan*/  CPU_RESET_CORE0_DEASSERT ; 
 int /*<<< orphan*/  KMD_MSG_FIT_RDY ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ SRAM_BASE_ADDR ; 
 scalar_t__ UBOOT_FW_OFFSET ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goya_init_golden_registers (struct hl_device*) ; 
 int goya_push_linux_to_device (struct hl_device*) ; 
 int goya_push_uboot_to_device (struct hl_device*) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mmCPU_CA53_CFG_ARM_RST_CONTROL ; 
 int /*<<< orphan*/  mmCPU_CA53_CFG_RST_ADDR_LSB_0 ; 
 int /*<<< orphan*/  mmCPU_CA53_CFG_RST_ADDR_MSB_0 ; 
 int /*<<< orphan*/  mmPSOC_GLOBAL_CONF_UBOOT_MAGIC ; 
 int /*<<< orphan*/  mmPSOC_GLOBAL_CONF_UNIT_RST_N ; 
 int /*<<< orphan*/  mmPSOC_GLOBAL_CONF_WARM_REBOOT ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int goya_pldm_init_cpu(struct hl_device *hdev)
{
	u32 val, unit_rst_val;
	int rc;

	/* Must initialize SRAM scrambler before pushing u-boot to SRAM */
	goya_init_golden_registers(hdev);

	/* Put ARM cores into reset */
	WREG32(mmCPU_CA53_CFG_ARM_RST_CONTROL, CPU_RESET_ASSERT);
	val = RREG32(mmCPU_CA53_CFG_ARM_RST_CONTROL);

	/* Reset the CA53 MACRO */
	unit_rst_val = RREG32(mmPSOC_GLOBAL_CONF_UNIT_RST_N);
	WREG32(mmPSOC_GLOBAL_CONF_UNIT_RST_N, CA53_RESET);
	val = RREG32(mmPSOC_GLOBAL_CONF_UNIT_RST_N);
	WREG32(mmPSOC_GLOBAL_CONF_UNIT_RST_N, unit_rst_val);
	val = RREG32(mmPSOC_GLOBAL_CONF_UNIT_RST_N);

	rc = goya_push_uboot_to_device(hdev);
	if (rc)
		return rc;

	rc = goya_push_linux_to_device(hdev);
	if (rc)
		return rc;

	WREG32(mmPSOC_GLOBAL_CONF_UBOOT_MAGIC, KMD_MSG_FIT_RDY);
	WREG32(mmPSOC_GLOBAL_CONF_WARM_REBOOT, CPU_BOOT_STATUS_NA);

	WREG32(mmCPU_CA53_CFG_RST_ADDR_LSB_0,
		lower_32_bits(SRAM_BASE_ADDR + UBOOT_FW_OFFSET));
	WREG32(mmCPU_CA53_CFG_RST_ADDR_MSB_0,
		upper_32_bits(SRAM_BASE_ADDR + UBOOT_FW_OFFSET));

	/* Release ARM core 0 from reset */
	WREG32(mmCPU_CA53_CFG_ARM_RST_CONTROL,
					CPU_RESET_CORE0_DEASSERT);
	val = RREG32(mmCPU_CA53_CFG_ARM_RST_CONTROL);

	return 0;
}