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
struct ide_info {int dummy; } ;
struct ide_host {scalar_t__* dev; struct ide_info* host_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ide_pci_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  kfree (struct ide_info*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct ide_host* pci_get_drvdata (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (scalar_t__) ; 

__attribute__((used)) static void hpt366_remove(struct pci_dev *dev)
{
	struct ide_host *host = pci_get_drvdata(dev);
	struct ide_info *info = host->host_priv;
	struct pci_dev *dev2 = host->dev[1] ? to_pci_dev(host->dev[1]) : NULL;

	ide_pci_remove(dev);
	pci_dev_put(dev2);
	kfree(info);
}