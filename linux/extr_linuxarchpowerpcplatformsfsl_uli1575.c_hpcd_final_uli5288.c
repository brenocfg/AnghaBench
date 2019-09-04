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
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  bus; } ;
struct pci_controller {int first_busno; struct device_node* dn; } ;
struct of_phandle_args {int* args; int args_count; struct device_node* np; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int PCI_DEVFN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_create_of_mapping (struct of_phandle_args*) ; 
 int /*<<< orphan*/  machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc86xx_hpcd ; 
 int /*<<< orphan*/  of_irq_parse_raw (int*,struct of_phandle_args*) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hpcd_final_uli5288(struct pci_dev *dev)
{
	struct pci_controller *hose = pci_bus_to_host(dev->bus);
	struct device_node *hosenode = hose ? hose->dn : NULL;
	struct of_phandle_args oirq;
	u32 laddr[3];

	if (!machine_is(mpc86xx_hpcd))
		return;

	if (!hosenode)
		return;

	oirq.np = hosenode;
	oirq.args[0] = 2;
	oirq.args_count = 1;
	laddr[0] = (hose->first_busno << 16) | (PCI_DEVFN(31, 0) << 8);
	laddr[1] = laddr[2] = 0;
	of_irq_parse_raw(laddr, &oirq);
	dev->irq = irq_create_of_mapping(&oirq);
}