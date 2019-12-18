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
struct pci_epc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN_ONCE (struct device*,int,char*) ; 
 int /*<<< orphan*/  devm_pci_epc_match ; 
 int /*<<< orphan*/  devm_pci_epc_release ; 
 int devres_destroy (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_epc*) ; 

void devm_pci_epc_destroy(struct device *dev, struct pci_epc *epc)
{
	int r;

	r = devres_destroy(dev, devm_pci_epc_release, devm_pci_epc_match,
			   epc);
	dev_WARN_ONCE(dev, r, "couldn't find PCI EPC resource\n");
}