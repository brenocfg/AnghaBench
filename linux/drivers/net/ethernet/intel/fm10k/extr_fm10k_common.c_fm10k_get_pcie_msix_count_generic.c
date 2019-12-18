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
typedef  int /*<<< orphan*/  u16 ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_MAX_MSIX_VECTORS ; 
 int /*<<< orphan*/  FM10K_PCI_MSIX_MSG_CTRL ; 
 int /*<<< orphan*/  FM10K_PCI_MSIX_MSG_CTRL_TBL_SZ_MASK ; 
 int /*<<< orphan*/  fm10k_read_pci_cfg_word (struct fm10k_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 fm10k_get_pcie_msix_count_generic(struct fm10k_hw *hw)
{
	u16 msix_count;

	/* read in value from MSI-X capability register */
	msix_count = fm10k_read_pci_cfg_word(hw, FM10K_PCI_MSIX_MSG_CTRL);
	msix_count &= FM10K_PCI_MSIX_MSG_CTRL_TBL_SZ_MASK;

	/* MSI-X count is zero-based in HW */
	msix_count++;

	if (msix_count > FM10K_MAX_MSIX_VECTORS)
		msix_count = FM10K_MAX_MSIX_VECTORS;

	return msix_count;
}