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
struct rt3883_pci_controller {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT3883_PCI_REG_PCIENA ; 
 struct rt3883_pci_controller* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int rt3883_pci_r32 (struct rt3883_pci_controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt3883_pci_w32 (struct rt3883_pci_controller*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt3883_pci_irq_unmask(struct irq_data *d)
{
	struct rt3883_pci_controller *rpc;
	u32 t;

	rpc = irq_data_get_irq_chip_data(d);

	t = rt3883_pci_r32(rpc, RT3883_PCI_REG_PCIENA);
	rt3883_pci_w32(rpc, t | BIT(d->hwirq), RT3883_PCI_REG_PCIENA);
	/* flush write */
	rt3883_pci_r32(rpc, RT3883_PCI_REG_PCIENA);
}