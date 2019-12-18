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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct rockchip_pcie {int dummy; } ;
struct rockchip_pcie_ep {int irq_pci_addr; int irq_pci_fn; scalar_t__ irq_cpu_addr; int /*<<< orphan*/  irq_phys_addr; scalar_t__ max_regions; struct rockchip_pcie rockchip; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXI_WRAPPER_MEM_WRITE ; 
 int EINVAL ; 
 int GENMASK_ULL (int,int) ; 
 scalar_t__ PCI_MSI_ADDRESS_HI ; 
 scalar_t__ PCI_MSI_ADDRESS_LO ; 
 scalar_t__ PCI_MSI_DATA_64 ; 
 scalar_t__ ROCKCHIP_PCIE_EP_FUNC_BASE (int) ; 
 int ROCKCHIP_PCIE_EP_MSI_CTRL_ME ; 
 int ROCKCHIP_PCIE_EP_MSI_CTRL_MME_MASK ; 
 int ROCKCHIP_PCIE_EP_MSI_CTRL_MME_OFFSET ; 
 scalar_t__ ROCKCHIP_PCIE_EP_MSI_CTRL_REG ; 
 int /*<<< orphan*/  rockchip_pcie_prog_ep_ob_atu (struct rockchip_pcie*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int rockchip_pcie_read (struct rockchip_pcie*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int rockchip_pcie_ep_send_msi_irq(struct rockchip_pcie_ep *ep, u8 fn,
					 u8 interrupt_num)
{
	struct rockchip_pcie *rockchip = &ep->rockchip;
	u16 flags, mme, data, data_mask;
	u8 msi_count;
	u64 pci_addr, pci_addr_mask = 0xff;

	/* Check MSI enable bit */
	flags = rockchip_pcie_read(&ep->rockchip,
				   ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				   ROCKCHIP_PCIE_EP_MSI_CTRL_REG);
	if (!(flags & ROCKCHIP_PCIE_EP_MSI_CTRL_ME))
		return -EINVAL;

	/* Get MSI numbers from MME */
	mme = ((flags & ROCKCHIP_PCIE_EP_MSI_CTRL_MME_MASK) >>
			ROCKCHIP_PCIE_EP_MSI_CTRL_MME_OFFSET);
	msi_count = 1 << mme;
	if (!interrupt_num || interrupt_num > msi_count)
		return -EINVAL;

	/* Set MSI private data */
	data_mask = msi_count - 1;
	data = rockchip_pcie_read(rockchip,
				  ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				  ROCKCHIP_PCIE_EP_MSI_CTRL_REG +
				  PCI_MSI_DATA_64);
	data = (data & ~data_mask) | ((interrupt_num - 1) & data_mask);

	/* Get MSI PCI address */
	pci_addr = rockchip_pcie_read(rockchip,
				      ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				      ROCKCHIP_PCIE_EP_MSI_CTRL_REG +
				      PCI_MSI_ADDRESS_HI);
	pci_addr <<= 32;
	pci_addr |= rockchip_pcie_read(rockchip,
				       ROCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				       ROCKCHIP_PCIE_EP_MSI_CTRL_REG +
				       PCI_MSI_ADDRESS_LO);
	pci_addr &= GENMASK_ULL(63, 2);

	/* Set the outbound region if needed. */
	if (unlikely(ep->irq_pci_addr != (pci_addr & ~pci_addr_mask) ||
		     ep->irq_pci_fn != fn)) {
		rockchip_pcie_prog_ep_ob_atu(rockchip, fn, ep->max_regions - 1,
					     AXI_WRAPPER_MEM_WRITE,
					     ep->irq_phys_addr,
					     pci_addr & ~pci_addr_mask,
					     pci_addr_mask + 1);
		ep->irq_pci_addr = (pci_addr & ~pci_addr_mask);
		ep->irq_pci_fn = fn;
	}

	writew(data, ep->irq_cpu_addr + (pci_addr & pci_addr_mask));
	return 0;
}