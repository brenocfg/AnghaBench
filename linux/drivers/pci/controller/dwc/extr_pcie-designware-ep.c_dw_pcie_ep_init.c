#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  unsigned int u32 ;
struct pci_epc {int max_functions; TYPE_2__* mem; } ;
struct dw_pcie_ep {void* msix_cap; void* msi_cap; int /*<<< orphan*/  msi_mem; int /*<<< orphan*/  msi_mem_phys; int /*<<< orphan*/  page_size; int /*<<< orphan*/  addr_size; int /*<<< orphan*/  phys_base; TYPE_1__* ops; struct pci_epc* epc; void* outbound_addr; int /*<<< orphan*/  num_ob_windows; void* ob_window_map; void* ib_window_map; int /*<<< orphan*/  num_ib_windows; } ;
struct dw_pcie {struct device* dev; int /*<<< orphan*/  dbi_base2; int /*<<< orphan*/  dbi_base; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  page_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ep_init ) (struct dw_pcie_ep*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pci_epc*) ; 
 int /*<<< orphan*/  MAX_IATU_IN ; 
 int /*<<< orphan*/  MAX_IATU_OUT ; 
 int /*<<< orphan*/  PCI_CAP_ID_MSI ; 
 int /*<<< orphan*/  PCI_CAP_ID_MSIX ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_REBAR ; 
 int /*<<< orphan*/  PCI_HEADER_TYPE ; 
 scalar_t__ PCI_HEADER_TYPE_NORMAL ; 
 scalar_t__ PCI_REBAR_CAP ; 
 scalar_t__ PCI_REBAR_CTRL ; 
 unsigned int PCI_REBAR_CTRL_NBAR_MASK ; 
 unsigned int PCI_REBAR_CTRL_NBAR_SHIFT ; 
 int PTR_ERR (struct pci_epc*) ; 
 int __pci_epc_mem_init (struct pci_epc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_kcalloc (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct pci_epc* devm_pci_epc_create (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dw_pcie_dbi_ro_wr_dis (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_dbi_ro_wr_en (struct dw_pcie*) ; 
 unsigned int dw_pcie_ep_find_ext_capability (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 void* dw_pcie_find_capability (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 scalar_t__ dw_pcie_readb_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 unsigned int dw_pcie_readl_dbi (struct dw_pcie*,scalar_t__) ; 
 int /*<<< orphan*/  dw_pcie_setup (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,scalar_t__,int) ; 
 int /*<<< orphan*/  epc_ops ; 
 int /*<<< orphan*/  epc_set_drvdata (struct pci_epc*,struct dw_pcie_ep*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u8 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  pci_epc_mem_alloc_addr (struct pci_epc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dw_pcie_ep*) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 

int dw_pcie_ep_init(struct dw_pcie_ep *ep)
{
	int i;
	int ret;
	u32 reg;
	void *addr;
	u8 hdr_type;
	unsigned int nbars;
	unsigned int offset;
	struct pci_epc *epc;
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	struct device *dev = pci->dev;
	struct device_node *np = dev->of_node;

	if (!pci->dbi_base || !pci->dbi_base2) {
		dev_err(dev, "dbi_base/dbi_base2 is not populated\n");
		return -EINVAL;
	}

	ret = of_property_read_u32(np, "num-ib-windows", &ep->num_ib_windows);
	if (ret < 0) {
		dev_err(dev, "Unable to read *num-ib-windows* property\n");
		return ret;
	}
	if (ep->num_ib_windows > MAX_IATU_IN) {
		dev_err(dev, "Invalid *num-ib-windows*\n");
		return -EINVAL;
	}

	ret = of_property_read_u32(np, "num-ob-windows", &ep->num_ob_windows);
	if (ret < 0) {
		dev_err(dev, "Unable to read *num-ob-windows* property\n");
		return ret;
	}
	if (ep->num_ob_windows > MAX_IATU_OUT) {
		dev_err(dev, "Invalid *num-ob-windows*\n");
		return -EINVAL;
	}

	ep->ib_window_map = devm_kcalloc(dev,
					 BITS_TO_LONGS(ep->num_ib_windows),
					 sizeof(long),
					 GFP_KERNEL);
	if (!ep->ib_window_map)
		return -ENOMEM;

	ep->ob_window_map = devm_kcalloc(dev,
					 BITS_TO_LONGS(ep->num_ob_windows),
					 sizeof(long),
					 GFP_KERNEL);
	if (!ep->ob_window_map)
		return -ENOMEM;

	addr = devm_kcalloc(dev, ep->num_ob_windows, sizeof(phys_addr_t),
			    GFP_KERNEL);
	if (!addr)
		return -ENOMEM;
	ep->outbound_addr = addr;

	epc = devm_pci_epc_create(dev, &epc_ops);
	if (IS_ERR(epc)) {
		dev_err(dev, "Failed to create epc device\n");
		return PTR_ERR(epc);
	}

	ep->epc = epc;
	epc_set_drvdata(epc, ep);

	if (ep->ops->ep_init)
		ep->ops->ep_init(ep);

	hdr_type = dw_pcie_readb_dbi(pci, PCI_HEADER_TYPE);
	if (hdr_type != PCI_HEADER_TYPE_NORMAL) {
		dev_err(pci->dev, "PCIe controller is not set to EP mode (hdr_type:0x%x)!\n",
			hdr_type);
		return -EIO;
	}

	ret = of_property_read_u8(np, "max-functions", &epc->max_functions);
	if (ret < 0)
		epc->max_functions = 1;

	ret = __pci_epc_mem_init(epc, ep->phys_base, ep->addr_size,
				 ep->page_size);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize address space\n");
		return ret;
	}

	ep->msi_mem = pci_epc_mem_alloc_addr(epc, &ep->msi_mem_phys,
					     epc->mem->page_size);
	if (!ep->msi_mem) {
		dev_err(dev, "Failed to reserve memory for MSI/MSI-X\n");
		return -ENOMEM;
	}
	ep->msi_cap = dw_pcie_find_capability(pci, PCI_CAP_ID_MSI);

	ep->msix_cap = dw_pcie_find_capability(pci, PCI_CAP_ID_MSIX);

	offset = dw_pcie_ep_find_ext_capability(pci, PCI_EXT_CAP_ID_REBAR);
	if (offset) {
		reg = dw_pcie_readl_dbi(pci, offset + PCI_REBAR_CTRL);
		nbars = (reg & PCI_REBAR_CTRL_NBAR_MASK) >>
			PCI_REBAR_CTRL_NBAR_SHIFT;

		dw_pcie_dbi_ro_wr_en(pci);
		for (i = 0; i < nbars; i++, offset += PCI_REBAR_CTRL)
			dw_pcie_writel_dbi(pci, offset + PCI_REBAR_CAP, 0x0);
		dw_pcie_dbi_ro_wr_dis(pci);
	}

	dw_pcie_setup(pci);

	return 0;
}