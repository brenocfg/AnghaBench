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
struct ide_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ide_host_remove (struct ide_host*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ide_host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void
delkin_cb_remove (struct pci_dev *dev)
{
	struct ide_host *host = pci_get_drvdata(dev);

	ide_host_remove(host);

	pci_release_regions(dev);
	pci_disable_device(dev);
}