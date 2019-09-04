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
struct via82cxxx_dev {int dummy; } ;
struct pci_dev {int dummy; } ;
struct ide_host {struct via82cxxx_dev* host_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ide_pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  kfree (struct via82cxxx_dev*) ; 
 struct ide_host* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void via_remove(struct pci_dev *dev)
{
	struct ide_host *host = pci_get_drvdata(dev);
	struct via82cxxx_dev *vdev = host->host_priv;

	ide_pci_remove(dev);
	kfree(vdev);
}