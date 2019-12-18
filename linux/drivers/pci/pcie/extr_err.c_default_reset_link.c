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
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int pci_bus_error_reset (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_printk (int /*<<< orphan*/ ,struct pci_dev*,char*) ; 

__attribute__((used)) static pci_ers_result_t default_reset_link(struct pci_dev *dev)
{
	int rc;

	rc = pci_bus_error_reset(dev);
	pci_printk(KERN_DEBUG, dev, "downstream link has been reset\n");
	return rc ? PCI_ERS_RESULT_DISCONNECT : PCI_ERS_RESULT_RECOVERED;
}