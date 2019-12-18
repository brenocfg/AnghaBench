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
typedef  int u64 ;
typedef  int u32 ;
struct octeon_device {int /*<<< orphan*/  pcie_port; int /*<<< orphan*/  pci_dev; } ;
typedef  enum octeon_pcie_mps { ____Placeholder_octeon_pcie_mps } octeon_pcie_mps ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_DPI_SLI_PRTX_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CN6XXX_PCIE_DEVCTL ; 
 int PCIE_MPS_DEFAULT ; 
 int lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_writeq (struct octeon_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void lio_cn6xxx_setup_pcie_mps(struct octeon_device *oct,
			       enum octeon_pcie_mps mps)
{
	u32 val;
	u64 r64;

	/* Read config register for MPS */
	pci_read_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, &val);

	if (mps == PCIE_MPS_DEFAULT) {
		mps = ((val & (0x7 << 5)) >> 5);
	} else {
		val &= ~(0x7 << 5);  /* Turn off any MPS bits */
		val |= (mps << 5);   /* Set MPS */
		pci_write_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, val);
	}

	/* Set MPS in DPI_SLI_PRT0_CFG to the same value. */
	r64 = lio_pci_readq(oct, CN6XXX_DPI_SLI_PRTX_CFG(oct->pcie_port));
	r64 |= (mps << 4);
	lio_pci_writeq(oct, r64, CN6XXX_DPI_SLI_PRTX_CFG(oct->pcie_port));
}