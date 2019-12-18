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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_LINK_STATE_L0S ; 
 int /*<<< orphan*/  pci_disable_link_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 

__attribute__((used)) static void quirk_disable_aspm_l0s(struct pci_dev *dev)
{
	pci_info(dev, "Disabling L0s\n");
	pci_disable_link_state(dev, PCIE_LINK_STATE_L0S);
}