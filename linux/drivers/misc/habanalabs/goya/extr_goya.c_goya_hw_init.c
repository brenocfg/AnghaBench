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
struct asic_fixed_properties {int dram_pci_bar_size; } ;
struct hl_device {int /*<<< orphan*/  dev; struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 scalar_t__ DRAM_PHYS_BASE ; 
 int EIO ; 
 int /*<<< orphan*/  GOYA_CPU_TIMEOUT_USEC ; 
 int /*<<< orphan*/  HL_DEVICE_HW_STATE_DIRTY ; 
 int MMU_PAGE_TABLES_ADDR ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 scalar_t__ U64_MAX ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  goya_disable_external_queues (struct hl_device*) ; 
 int /*<<< orphan*/  goya_disable_internal_queues (struct hl_device*) ; 
 int goya_enable_msix (struct hl_device*) ; 
 int /*<<< orphan*/  goya_enable_timestamp (struct hl_device*) ; 
 int goya_init_cpu (struct hl_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goya_init_dma_qmans (struct hl_device*) ; 
 int /*<<< orphan*/  goya_init_golden_registers (struct hl_device*) ; 
 int /*<<< orphan*/  goya_init_mme_qmans (struct hl_device*) ; 
 int /*<<< orphan*/  goya_init_security (struct hl_device*) ; 
 int /*<<< orphan*/  goya_init_tpc_qmans (struct hl_device*) ; 
 int goya_mmu_init (struct hl_device*) ; 
 scalar_t__ goya_set_ddr_bar_base (struct hl_device*,scalar_t__) ; 
 int /*<<< orphan*/  goya_tpc_mbist_workaround (struct hl_device*) ; 
 int /*<<< orphan*/  mmHW_STATE ; 
 int /*<<< orphan*/  mmPCIE_DBI_DEVICE_ID_VENDOR_ID_REG ; 

__attribute__((used)) static int goya_hw_init(struct hl_device *hdev)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	u32 val;
	int rc;

	dev_info(hdev->dev, "Starting initialization of H/W\n");

	/* Perform read from the device to make sure device is up */
	val = RREG32(mmPCIE_DBI_DEVICE_ID_VENDOR_ID_REG);

	/*
	 * Let's mark in the H/W that we have reached this point. We check
	 * this value in the reset_before_init function to understand whether
	 * we need to reset the chip before doing H/W init. This register is
	 * cleared by the H/W upon H/W reset
	 */
	WREG32(mmHW_STATE, HL_DEVICE_HW_STATE_DIRTY);

	rc = goya_init_cpu(hdev, GOYA_CPU_TIMEOUT_USEC);
	if (rc) {
		dev_err(hdev->dev, "failed to initialize CPU\n");
		return rc;
	}

	goya_tpc_mbist_workaround(hdev);

	goya_init_golden_registers(hdev);

	/*
	 * After CPU initialization is finished, change DDR bar mapping inside
	 * iATU to point to the start address of the MMU page tables
	 */
	if (goya_set_ddr_bar_base(hdev, DRAM_PHYS_BASE +
			(MMU_PAGE_TABLES_ADDR &
			~(prop->dram_pci_bar_size - 0x1ull))) == U64_MAX) {
		dev_err(hdev->dev,
			"failed to map DDR bar to MMU page tables\n");
		return -EIO;
	}

	rc = goya_mmu_init(hdev);
	if (rc)
		return rc;

	goya_init_security(hdev);

	goya_init_dma_qmans(hdev);

	goya_init_mme_qmans(hdev);

	goya_init_tpc_qmans(hdev);

	goya_enable_timestamp(hdev);

	/* MSI-X must be enabled before CPU queues are initialized */
	rc = goya_enable_msix(hdev);
	if (rc)
		goto disable_queues;

	/* Perform read from the device to flush all MSI-X configuration */
	val = RREG32(mmPCIE_DBI_DEVICE_ID_VENDOR_ID_REG);

	return 0;

disable_queues:
	goya_disable_internal_queues(hdev);
	goya_disable_external_queues(hdev);

	return rc;
}