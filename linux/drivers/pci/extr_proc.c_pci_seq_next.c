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
struct seq_file {int dummy; } ;
typedef  void pci_dev ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ANY_ID ; 
 void* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void *pci_seq_next(struct seq_file *m, void *v, loff_t *pos)
{
	struct pci_dev *dev = v;

	(*pos)++;
	dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, dev);
	return dev;
}