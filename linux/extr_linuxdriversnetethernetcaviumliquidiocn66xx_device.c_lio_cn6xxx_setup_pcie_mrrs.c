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
typedef  enum octeon_pcie_mrrs { ____Placeholder_octeon_pcie_mrrs } octeon_pcie_mrrs ;

/* Variables and functions */
 int /*<<< orphan*/  CN6XXX_DPI_SLI_PRTX_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CN6XXX_PCIE_DEVCTL ; 
 int /*<<< orphan*/  CN6XXX_SLI_S2M_PORTX_CTL (int /*<<< orphan*/ ) ; 
 int PCIE_MRRS_DEFAULT ; 
 int lio_pci_readq (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_pci_writeq (struct octeon_device*,int,int /*<<< orphan*/ ) ; 
 int octeon_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void lio_cn6xxx_setup_pcie_mrrs(struct octeon_device *oct,
				enum octeon_pcie_mrrs mrrs)
{
	u32 val;
	u64 r64;

	/* Read config register for MRRS */
	pci_read_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, &val);

	if (mrrs == PCIE_MRRS_DEFAULT) {
		mrrs = ((val & (0x7 << 12)) >> 12);
	} else {
		val &= ~(0x7 << 12); /* Turn off any MRRS bits */
		val |= (mrrs << 12); /* Set MRRS */
		pci_write_config_dword(oct->pci_dev, CN6XXX_PCIE_DEVCTL, val);
	}

	/* Set MRRS in SLI_S2M_PORT0_CTL to the same value. */
	r64 = octeon_read_csr64(oct, CN6XXX_SLI_S2M_PORTX_CTL(oct->pcie_port));
	r64 |= mrrs;
	octeon_write_csr64(oct, CN6XXX_SLI_S2M_PORTX_CTL(oct->pcie_port), r64);

	/* Set MRRS in DPI_SLI_PRT0_CFG to the same value. */
	r64 = lio_pci_readq(oct, CN6XXX_DPI_SLI_PRTX_CFG(oct->pcie_port));
	r64 |= mrrs;
	lio_pci_writeq(oct, r64, CN6XXX_DPI_SLI_PRTX_CFG(oct->pcie_port));
}