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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int PCIE_INTR_CE_MASK_ALL ; 
 scalar_t__ PCIE_INTR_ENABLE_ADDRESS ; 
 int PCIE_INTR_FIRMWARE_MASK ; 
 scalar_t__ SOC_CORE_BASE_ADDRESS ; 
 int /*<<< orphan*/  ath10k_pci_read32 (struct ath10k*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_pci_write32 (struct ath10k*,scalar_t__,int) ; 

void ath10k_pci_enable_legacy_irq(struct ath10k *ar)
{
	ath10k_pci_write32(ar, SOC_CORE_BASE_ADDRESS +
			   PCIE_INTR_ENABLE_ADDRESS,
			   PCIE_INTR_FIRMWARE_MASK | PCIE_INTR_CE_MASK_ALL);

	/* IMPORTANT: this extra read transaction is required to
	 * flush the posted write buffer.
	 */
	(void)ath10k_pci_read32(ar, SOC_CORE_BASE_ADDRESS +
				PCIE_INTR_ENABLE_ADDRESS);
}