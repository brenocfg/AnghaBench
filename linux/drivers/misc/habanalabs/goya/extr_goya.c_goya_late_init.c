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
struct asic_fixed_properties {int /*<<< orphan*/  dram_size; } ;
struct hl_device {int /*<<< orphan*/  dev; struct asic_fixed_properties asic_prop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARMCP_PACKET_ENABLE_PCI_ACCESS ; 
 int /*<<< orphan*/  GOYA_ASYNC_EVENT_ID_INTS_REGISTER ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int goya_armcp_info_get (struct hl_device*) ; 
 int /*<<< orphan*/  goya_fetch_psoc_frequency (struct hl_device*) ; 
 int goya_init_cpu_queues (struct hl_device*) ; 
 int goya_mmu_add_mappings_for_device_cpu (struct hl_device*) ; 
 int goya_mmu_clear_pgt_range (struct hl_device*) ; 
 int goya_mmu_set_dram_default_page (struct hl_device*) ; 
 int goya_test_cpu_queue (struct hl_device*) ; 
 int hl_fw_send_pci_access_msg (struct hl_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR ; 
 int /*<<< orphan*/  mmMMU_LOG2_DDR_SIZE ; 

int goya_late_init(struct hl_device *hdev)
{
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	int rc;

	goya_fetch_psoc_frequency(hdev);

	rc = goya_mmu_clear_pgt_range(hdev);
	if (rc) {
		dev_err(hdev->dev,
			"Failed to clear MMU page tables range %d\n", rc);
		return rc;
	}

	rc = goya_mmu_set_dram_default_page(hdev);
	if (rc) {
		dev_err(hdev->dev, "Failed to set DRAM default page %d\n", rc);
		return rc;
	}

	rc = goya_mmu_add_mappings_for_device_cpu(hdev);
	if (rc)
		return rc;

	rc = goya_init_cpu_queues(hdev);
	if (rc)
		return rc;

	rc = goya_test_cpu_queue(hdev);
	if (rc)
		return rc;

	rc = goya_armcp_info_get(hdev);
	if (rc) {
		dev_err(hdev->dev, "Failed to get armcp info %d\n", rc);
		return rc;
	}

	/* Now that we have the DRAM size in ASIC prop, we need to check
	 * its size and configure the DMA_IF DDR wrap protection (which is in
	 * the MMU block) accordingly. The value is the log2 of the DRAM size
	 */
	WREG32(mmMMU_LOG2_DDR_SIZE, ilog2(prop->dram_size));

	rc = hl_fw_send_pci_access_msg(hdev, ARMCP_PACKET_ENABLE_PCI_ACCESS);
	if (rc) {
		dev_err(hdev->dev,
			"Failed to enable PCI access from CPU %d\n", rc);
		return rc;
	}

	WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR,
			GOYA_ASYNC_EVENT_ID_INTS_REGISTER);

	return 0;
}