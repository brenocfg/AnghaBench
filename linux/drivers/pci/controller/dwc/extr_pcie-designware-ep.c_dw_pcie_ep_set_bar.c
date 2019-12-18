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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct pci_epf_bar {int barno; size_t size; int flags; int /*<<< orphan*/  phys_addr; } ;
struct pci_epc {int dummy; } ;
struct dw_pcie_ep {int dummy; } ;
struct dw_pcie {int dummy; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;
typedef  enum dw_pcie_as_type { ____Placeholder_dw_pcie_as_type } dw_pcie_as_type ;

/* Variables and functions */
 int DW_PCIE_AS_IO ; 
 int DW_PCIE_AS_MEM ; 
 scalar_t__ PCI_BASE_ADDRESS_0 ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_64 ; 
 int PCI_BASE_ADDRESS_SPACE ; 
 int /*<<< orphan*/  dw_pcie_dbi_ro_wr_dis (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_dbi_ro_wr_en (struct dw_pcie*) ; 
 int dw_pcie_ep_inbound_atu (struct dw_pcie_ep*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,scalar_t__,int) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi2 (struct dw_pcie*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dw_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 int /*<<< orphan*/  lower_32_bits (size_t) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 
 int /*<<< orphan*/  upper_32_bits (size_t) ; 

__attribute__((used)) static int dw_pcie_ep_set_bar(struct pci_epc *epc, u8 func_no,
			      struct pci_epf_bar *epf_bar)
{
	int ret;
	struct dw_pcie_ep *ep = epc_get_drvdata(epc);
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	enum pci_barno bar = epf_bar->barno;
	size_t size = epf_bar->size;
	int flags = epf_bar->flags;
	enum dw_pcie_as_type as_type;
	u32 reg = PCI_BASE_ADDRESS_0 + (4 * bar);

	if (!(flags & PCI_BASE_ADDRESS_SPACE))
		as_type = DW_PCIE_AS_MEM;
	else
		as_type = DW_PCIE_AS_IO;

	ret = dw_pcie_ep_inbound_atu(ep, bar, epf_bar->phys_addr, as_type);
	if (ret)
		return ret;

	dw_pcie_dbi_ro_wr_en(pci);

	dw_pcie_writel_dbi2(pci, reg, lower_32_bits(size - 1));
	dw_pcie_writel_dbi(pci, reg, flags);

	if (flags & PCI_BASE_ADDRESS_MEM_TYPE_64) {
		dw_pcie_writel_dbi2(pci, reg + 4, upper_32_bits(size - 1));
		dw_pcie_writel_dbi(pci, reg + 4, 0);
	}

	dw_pcie_dbi_ro_wr_dis(pci);

	return 0;
}