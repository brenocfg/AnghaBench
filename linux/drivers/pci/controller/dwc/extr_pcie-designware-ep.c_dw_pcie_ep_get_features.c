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
typedef  int /*<<< orphan*/  u8 ;
struct pci_epc_features {int dummy; } ;
struct pci_epc {int dummy; } ;
struct dw_pcie_ep {TYPE_1__* ops; } ;
struct TYPE_2__ {struct pci_epc_features const* (* get_features ) (struct dw_pcie_ep*) ;} ;

/* Variables and functions */
 struct dw_pcie_ep* epc_get_drvdata (struct pci_epc*) ; 
 struct pci_epc_features const* stub1 (struct dw_pcie_ep*) ; 

__attribute__((used)) static const struct pci_epc_features*
dw_pcie_ep_get_features(struct pci_epc *epc, u8 func_no)
{
	struct dw_pcie_ep *ep = epc_get_drvdata(epc);

	if (!ep->ops->get_features)
		return NULL;

	return ep->ops->get_features(ep);
}