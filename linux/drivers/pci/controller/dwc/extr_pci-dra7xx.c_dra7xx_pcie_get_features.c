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
struct pci_epc_features {int dummy; } ;
struct dw_pcie_ep {int dummy; } ;

/* Variables and functions */
 struct pci_epc_features const dra7xx_pcie_epc_features ; 

__attribute__((used)) static const struct pci_epc_features*
dra7xx_pcie_get_features(struct dw_pcie_ep *ep)
{
	return &dra7xx_pcie_epc_features;
}