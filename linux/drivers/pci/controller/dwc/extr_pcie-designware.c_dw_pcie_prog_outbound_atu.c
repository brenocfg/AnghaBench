#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct dw_pcie {int /*<<< orphan*/  dev; scalar_t__ iatu_unroll_enabled; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* cpu_addr_fixup ) (struct dw_pcie*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_WAIT_IATU ; 
 scalar_t__ LINK_WAIT_MAX_IATU_RETRIES ; 
 int /*<<< orphan*/  PCIE_ATU_CR1 ; 
 int /*<<< orphan*/  PCIE_ATU_CR2 ; 
 scalar_t__ PCIE_ATU_ENABLE ; 
 int /*<<< orphan*/  PCIE_ATU_LIMIT ; 
 int /*<<< orphan*/  PCIE_ATU_LOWER_BASE ; 
 int /*<<< orphan*/  PCIE_ATU_LOWER_TARGET ; 
 int PCIE_ATU_REGION_OUTBOUND ; 
 int /*<<< orphan*/  PCIE_ATU_UPPER_BASE ; 
 int /*<<< orphan*/  PCIE_ATU_UPPER_TARGET ; 
 int /*<<< orphan*/  PCIE_ATU_VIEWPORT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dw_pcie_prog_outbound_atu_unroll (struct dw_pcie*,int,int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ dw_pcie_readl_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dw_pcie*,scalar_t__) ; 
 scalar_t__ upper_32_bits (scalar_t__) ; 

void dw_pcie_prog_outbound_atu(struct dw_pcie *pci, int index, int type,
			       u64 cpu_addr, u64 pci_addr, u32 size)
{
	u32 retries, val;

	if (pci->ops->cpu_addr_fixup)
		cpu_addr = pci->ops->cpu_addr_fixup(pci, cpu_addr);

	if (pci->iatu_unroll_enabled) {
		dw_pcie_prog_outbound_atu_unroll(pci, index, type, cpu_addr,
						 pci_addr, size);
		return;
	}

	dw_pcie_writel_dbi(pci, PCIE_ATU_VIEWPORT,
			   PCIE_ATU_REGION_OUTBOUND | index);
	dw_pcie_writel_dbi(pci, PCIE_ATU_LOWER_BASE,
			   lower_32_bits(cpu_addr));
	dw_pcie_writel_dbi(pci, PCIE_ATU_UPPER_BASE,
			   upper_32_bits(cpu_addr));
	dw_pcie_writel_dbi(pci, PCIE_ATU_LIMIT,
			   lower_32_bits(cpu_addr + size - 1));
	dw_pcie_writel_dbi(pci, PCIE_ATU_LOWER_TARGET,
			   lower_32_bits(pci_addr));
	dw_pcie_writel_dbi(pci, PCIE_ATU_UPPER_TARGET,
			   upper_32_bits(pci_addr));
	dw_pcie_writel_dbi(pci, PCIE_ATU_CR1, type);
	dw_pcie_writel_dbi(pci, PCIE_ATU_CR2, PCIE_ATU_ENABLE);

	/*
	 * Make sure ATU enable takes effect before any subsequent config
	 * and I/O accesses.
	 */
	for (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) {
		val = dw_pcie_readl_dbi(pci, PCIE_ATU_CR2);
		if (val & PCIE_ATU_ENABLE)
			return;

		mdelay(LINK_WAIT_IATU);
	}
	dev_err(pci->dev, "Outbound iATU is not being enabled\n");
}