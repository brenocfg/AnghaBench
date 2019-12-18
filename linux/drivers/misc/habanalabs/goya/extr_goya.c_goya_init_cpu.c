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
typedef  int u32 ;
struct hl_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  fw_loading; scalar_t__ pldm; int /*<<< orphan*/  cpu_enable; struct goya_device* asic_specific; } ;
struct goya_device {int hw_cap_initialized; } ;

/* Variables and functions */
#define  CPU_BOOT_STATUS_DRAM_INIT_FAIL 135 
 int CPU_BOOT_STATUS_DRAM_RDY ; 
 int CPU_BOOT_STATUS_FIT_CORRUPTED ; 
#define  CPU_BOOT_STATUS_IN_BTL 134 
#define  CPU_BOOT_STATUS_IN_PREBOOT 133 
#define  CPU_BOOT_STATUS_IN_SPL 132 
#define  CPU_BOOT_STATUS_IN_UBOOT 131 
#define  CPU_BOOT_STATUS_IN_WFE 130 
#define  CPU_BOOT_STATUS_NA 129 
 int CPU_BOOT_STATUS_SRAM_AVAIL ; 
#define  CPU_BOOT_STATUS_UBOOT_NOT_READY 128 
 int /*<<< orphan*/  DRAM_PHYS_BASE ; 
 int EIO ; 
 int /*<<< orphan*/  FW_COMP_PREBOOT ; 
 int /*<<< orphan*/  FW_COMP_UBOOT ; 
 int HW_CAP_CPU ; 
 int /*<<< orphan*/  KMD_MSG_FIT_RDY ; 
 int /*<<< orphan*/  KMD_MSG_NA ; 
 scalar_t__ U64_MAX ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int goya_pldm_init_cpu (struct hl_device*) ; 
 int goya_push_linux_to_device (struct hl_device*) ; 
 int /*<<< orphan*/  goya_read_device_fw_version (struct hl_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ goya_set_ddr_bar_base (struct hl_device*,int /*<<< orphan*/ ) ; 
 int hl_poll_timeout (struct hl_device*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  mmPSOC_GLOBAL_CONF_UBOOT_MAGIC ; 
 int /*<<< orphan*/  mmPSOC_GLOBAL_CONF_WARM_REBOOT ; 

__attribute__((used)) static int goya_init_cpu(struct hl_device *hdev, u32 cpu_timeout)
{
	struct goya_device *goya = hdev->asic_specific;
	u32 status;
	int rc;

	if (!hdev->cpu_enable)
		return 0;

	if (goya->hw_cap_initialized & HW_CAP_CPU)
		return 0;

	/*
	 * Before pushing u-boot/linux to device, need to set the ddr bar to
	 * base address of dram
	 */
	if (goya_set_ddr_bar_base(hdev, DRAM_PHYS_BASE) == U64_MAX) {
		dev_err(hdev->dev,
			"failed to map DDR bar to DRAM base address\n");
		return -EIO;
	}

	if (hdev->pldm) {
		rc = goya_pldm_init_cpu(hdev);
		if (rc)
			return rc;

		goto out;
	}

	/* Make sure CPU boot-loader is running */
	rc = hl_poll_timeout(
		hdev,
		mmPSOC_GLOBAL_CONF_WARM_REBOOT,
		status,
		(status == CPU_BOOT_STATUS_DRAM_RDY) ||
		(status == CPU_BOOT_STATUS_SRAM_AVAIL),
		10000,
		cpu_timeout);

	if (rc) {
		dev_err(hdev->dev, "Error in ARM u-boot!");
		switch (status) {
		case CPU_BOOT_STATUS_NA:
			dev_err(hdev->dev,
				"ARM status %d - BTL did NOT run\n", status);
			break;
		case CPU_BOOT_STATUS_IN_WFE:
			dev_err(hdev->dev,
				"ARM status %d - Inside WFE loop\n", status);
			break;
		case CPU_BOOT_STATUS_IN_BTL:
			dev_err(hdev->dev,
				"ARM status %d - Stuck in BTL\n", status);
			break;
		case CPU_BOOT_STATUS_IN_PREBOOT:
			dev_err(hdev->dev,
				"ARM status %d - Stuck in Preboot\n", status);
			break;
		case CPU_BOOT_STATUS_IN_SPL:
			dev_err(hdev->dev,
				"ARM status %d - Stuck in SPL\n", status);
			break;
		case CPU_BOOT_STATUS_IN_UBOOT:
			dev_err(hdev->dev,
				"ARM status %d - Stuck in u-boot\n", status);
			break;
		case CPU_BOOT_STATUS_DRAM_INIT_FAIL:
			dev_err(hdev->dev,
				"ARM status %d - DDR initialization failed\n",
				status);
			break;
		case CPU_BOOT_STATUS_UBOOT_NOT_READY:
			dev_err(hdev->dev,
				"ARM status %d - u-boot stopped by user\n",
				status);
			break;
		default:
			dev_err(hdev->dev,
				"ARM status %d - Invalid status code\n",
				status);
			break;
		}
		return -EIO;
	}

	/* Read U-Boot version now in case we will later fail */
	goya_read_device_fw_version(hdev, FW_COMP_UBOOT);
	goya_read_device_fw_version(hdev, FW_COMP_PREBOOT);

	if (!hdev->fw_loading) {
		dev_info(hdev->dev, "Skip loading FW\n");
		goto out;
	}

	if (status == CPU_BOOT_STATUS_SRAM_AVAIL)
		goto out;

	rc = goya_push_linux_to_device(hdev);
	if (rc)
		return rc;

	WREG32(mmPSOC_GLOBAL_CONF_UBOOT_MAGIC, KMD_MSG_FIT_RDY);

	rc = hl_poll_timeout(
		hdev,
		mmPSOC_GLOBAL_CONF_WARM_REBOOT,
		status,
		(status == CPU_BOOT_STATUS_SRAM_AVAIL),
		10000,
		cpu_timeout);

	if (rc) {
		if (status == CPU_BOOT_STATUS_FIT_CORRUPTED)
			dev_err(hdev->dev,
				"ARM u-boot reports FIT image is corrupted\n");
		else
			dev_err(hdev->dev,
				"ARM Linux failed to load, %d\n", status);
		WREG32(mmPSOC_GLOBAL_CONF_UBOOT_MAGIC, KMD_MSG_NA);
		return -EIO;
	}

	dev_info(hdev->dev, "Successfully loaded firmware to device\n");

out:
	goya->hw_cap_initialized |= HW_CAP_CPU;

	return 0;
}