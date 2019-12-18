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
struct pci_epc_features {int dummy; } ;
struct pci_epc {int dummy; } ;

/* Variables and functions */
 struct pci_epc_features const cdns_pcie_epc_features ; 

__attribute__((used)) static const struct pci_epc_features*
cdns_pcie_ep_get_features(struct pci_epc *epc, u8 func_no)
{
	return &cdns_pcie_epc_features;
}