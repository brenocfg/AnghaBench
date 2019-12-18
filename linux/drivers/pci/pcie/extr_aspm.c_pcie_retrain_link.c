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
typedef  int u16 ;
struct pcie_link_state {struct pci_dev* pdev; } ;
struct pci_dev {scalar_t__ clear_retrain_link; } ;

/* Variables and functions */
 unsigned long LINK_RETRAIN_TIMEOUT ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_RL ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_LT ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static bool pcie_retrain_link(struct pcie_link_state *link)
{
	struct pci_dev *parent = link->pdev;
	unsigned long end_jiffies;
	u16 reg16;

	pcie_capability_read_word(parent, PCI_EXP_LNKCTL, &reg16);
	reg16 |= PCI_EXP_LNKCTL_RL;
	pcie_capability_write_word(parent, PCI_EXP_LNKCTL, reg16);
	if (parent->clear_retrain_link) {
		/*
		 * Due to an erratum in some devices the Retrain Link bit
		 * needs to be cleared again manually to allow the link
		 * training to succeed.
		 */
		reg16 &= ~PCI_EXP_LNKCTL_RL;
		pcie_capability_write_word(parent, PCI_EXP_LNKCTL, reg16);
	}

	/* Wait for link training end. Break out after waiting for timeout */
	end_jiffies = jiffies + LINK_RETRAIN_TIMEOUT;
	do {
		pcie_capability_read_word(parent, PCI_EXP_LNKSTA, &reg16);
		if (!(reg16 & PCI_EXP_LNKSTA_LT))
			break;
		msleep(1);
	} while (time_before(jiffies, end_jiffies));
	return !(reg16 & PCI_EXP_LNKSTA_LT);
}