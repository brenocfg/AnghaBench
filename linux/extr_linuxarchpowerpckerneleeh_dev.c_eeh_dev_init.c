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
struct pci_dn {struct eeh_dev* edev; } ;
struct eeh_dev {int /*<<< orphan*/  rmv_list; int /*<<< orphan*/  list; struct pci_dn* pdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct eeh_dev* kzalloc (int,int /*<<< orphan*/ ) ; 

struct eeh_dev *eeh_dev_init(struct pci_dn *pdn)
{
	struct eeh_dev *edev;

	/* Allocate EEH device */
	edev = kzalloc(sizeof(*edev), GFP_KERNEL);
	if (!edev)
		return NULL;

	/* Associate EEH device with OF node */
	pdn->edev = edev;
	edev->pdn = pdn;
	INIT_LIST_HEAD(&edev->list);
	INIT_LIST_HEAD(&edev->rmv_list);

	return edev;
}