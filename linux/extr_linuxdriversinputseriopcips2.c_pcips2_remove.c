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
struct pcips2_data {int /*<<< orphan*/  io; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pcips2_data*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pcips2_data* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  serio_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcips2_remove(struct pci_dev *dev)
{
	struct pcips2_data *ps2if = pci_get_drvdata(dev);

	serio_unregister_port(ps2if->io);
	kfree(ps2if);
	pci_release_regions(dev);
	pci_disable_device(dev);
}