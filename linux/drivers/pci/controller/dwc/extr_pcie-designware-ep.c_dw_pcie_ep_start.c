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
struct pci_epc {int dummy; } ;
struct dw_pcie_ep {int dummy; } ;
struct dw_pcie {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* start_link ) (struct dw_pcie*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct dw_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 int stub1 (struct dw_pcie*) ; 
 struct dw_pcie* to_dw_pcie_from_ep (struct dw_pcie_ep*) ; 

__attribute__((used)) static int dw_pcie_ep_start(struct pci_epc *epc)
{
	struct dw_pcie_ep *ep = epc_get_drvdata(epc);
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);

	if (!pci->ops->start_link)
		return -EINVAL;

	return pci->ops->start_link(pci);
}