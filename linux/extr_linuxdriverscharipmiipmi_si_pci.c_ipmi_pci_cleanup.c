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
struct si_sm_io {struct pci_dev* addr_source_data; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 

__attribute__((used)) static void ipmi_pci_cleanup(struct si_sm_io *io)
{
	struct pci_dev *pdev = io->addr_source_data;

	pci_disable_device(pdev);
}