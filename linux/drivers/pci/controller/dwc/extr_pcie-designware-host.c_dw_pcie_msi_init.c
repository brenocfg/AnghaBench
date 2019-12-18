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
typedef  scalar_t__ u64 ;
struct pcie_port {scalar_t__ msi_data; int /*<<< orphan*/ * msi_page; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCIE_MSI_ADDR_HI ; 
 int /*<<< orphan*/  PCIE_MSI_ADDR_LO ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dma_map_page (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  dw_pcie_wr_own_conf (struct pcie_port*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

void dw_pcie_msi_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct device *dev = pci->dev;
	u64 msi_target;

	pp->msi_page = alloc_page(GFP_KERNEL);
	pp->msi_data = dma_map_page(dev, pp->msi_page, 0, PAGE_SIZE,
				    DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, pp->msi_data)) {
		dev_err(dev, "Failed to map MSI data\n");
		__free_page(pp->msi_page);
		pp->msi_page = NULL;
		return;
	}
	msi_target = (u64)pp->msi_data;

	/* Program the msi_data */
	dw_pcie_wr_own_conf(pp, PCIE_MSI_ADDR_LO, 4,
			    lower_32_bits(msi_target));
	dw_pcie_wr_own_conf(pp, PCIE_MSI_ADDR_HI, 4,
			    upper_32_bits(msi_target));
}