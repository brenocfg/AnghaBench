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
struct list_head {int dummy; } ;
struct pci_host_bridge {struct list_head windows; } ;
struct mtk_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_resource_list (struct list_head*) ; 
 struct pci_host_bridge* pci_host_bridge_from_priv (struct mtk_pcie*) ; 

__attribute__((used)) static void mtk_pcie_free_resources(struct mtk_pcie *pcie)
{
	struct pci_host_bridge *host = pci_host_bridge_from_priv(pcie);
	struct list_head *windows = &host->windows;

	pci_free_resource_list(windows);
}