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
struct pci_dn {int dummy; } ;
struct eeh_dev {int* config_space; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_config ) (struct pci_dn*,int,int,int) ;} ;

/* Variables and functions */
 int PCI_CACHE_LINE_SIZE ; 
 int PCI_COMMAND ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int PCI_LATENCY_TIMER ; 
 int SAVED_BYTE (int) ; 
 int /*<<< orphan*/  eeh_bridge_check_link (struct eeh_dev*) ; 
 struct pci_dn* eeh_dev_to_pdn (struct eeh_dev*) ; 
 TYPE_1__* eeh_ops ; 
 int /*<<< orphan*/  stub1 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub3 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub4 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub5 (struct pci_dn*,int,int,int) ; 
 int /*<<< orphan*/  stub6 (struct pci_dn*,int,int,int) ; 

__attribute__((used)) static void eeh_restore_bridge_bars(struct eeh_dev *edev)
{
	struct pci_dn *pdn = eeh_dev_to_pdn(edev);
	int i;

	/*
	 * Device BARs: 0x10 - 0x18
	 * Bus numbers and windows: 0x18 - 0x30
	 */
	for (i = 4; i < 13; i++)
		eeh_ops->write_config(pdn, i*4, 4, edev->config_space[i]);
	/* Rom: 0x38 */
	eeh_ops->write_config(pdn, 14*4, 4, edev->config_space[14]);

	/* Cache line & Latency timer: 0xC 0xD */
	eeh_ops->write_config(pdn, PCI_CACHE_LINE_SIZE, 1,
                SAVED_BYTE(PCI_CACHE_LINE_SIZE));
        eeh_ops->write_config(pdn, PCI_LATENCY_TIMER, 1,
                SAVED_BYTE(PCI_LATENCY_TIMER));
	/* Max latency, min grant, interrupt ping and line: 0x3C */
	eeh_ops->write_config(pdn, 15*4, 4, edev->config_space[15]);

	/* PCI Command: 0x4 */
	eeh_ops->write_config(pdn, PCI_COMMAND, 4, edev->config_space[1] |
			      PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);

	/* Check the PCIe link is ready */
	eeh_bridge_check_link(edev);
}