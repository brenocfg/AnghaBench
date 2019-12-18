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
struct whci_card {int n_caps; int /*<<< orphan*/  uwbbase; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UWBCAPDATA_SIZE (int) ; 
 int /*<<< orphan*/  kfree (struct whci_card*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct whci_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  whci_del_cap (struct whci_card*,int) ; 

__attribute__((used)) static void whci_remove(struct pci_dev *pci)
{
	struct whci_card *card = pci_get_drvdata(pci);
	int n;

	pci_set_drvdata(pci, NULL);
	/* Unregister each capability in reverse (so the master device
	 * is unregistered last). */
	for (n = card->n_caps; n >= 0 ; n--)
		whci_del_cap(card, n);
	pci_iounmap(pci, card->uwbbase);
	release_mem_region(pci_resource_start(pci, 0), UWBCAPDATA_SIZE(card->n_caps));
	kfree(card);
	pci_disable_msi(pci);
	pci_disable_device(pci);
}