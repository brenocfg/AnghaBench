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
 int /*<<< orphan*/  hpwdt_dev ; 
 int /*<<< orphan*/  hpwdt_exit_nmi_decoding () ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_mem_addr ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hpwdt_exit(struct pci_dev *dev)
{
	watchdog_unregister_device(&hpwdt_dev);
	hpwdt_exit_nmi_decoding();
	pci_iounmap(dev, pci_mem_addr);
	pci_disable_device(dev);
}