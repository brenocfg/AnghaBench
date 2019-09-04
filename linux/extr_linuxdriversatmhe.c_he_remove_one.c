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
struct he_dev {int dummy; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 struct he_dev* HE_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  atm_dev_deregister (struct atm_dev*) ; 
 int /*<<< orphan*/  he_stop (struct he_dev*) ; 
 int /*<<< orphan*/  kfree (struct he_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct atm_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void he_remove_one(struct pci_dev *pci_dev)
{
	struct atm_dev *atm_dev;
	struct he_dev *he_dev;

	atm_dev = pci_get_drvdata(pci_dev);
	he_dev = HE_DEV(atm_dev);

	/* need to remove from he_devs */

	he_stop(he_dev);
	atm_dev_deregister(atm_dev);
	kfree(he_dev);

	pci_disable_device(pci_dev);
}