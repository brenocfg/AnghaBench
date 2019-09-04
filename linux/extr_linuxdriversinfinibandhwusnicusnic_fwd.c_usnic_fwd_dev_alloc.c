#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usnic_fwd_dev {TYPE_1__* netdev; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usnic_fwd_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct usnic_fwd_dev *usnic_fwd_dev_alloc(struct pci_dev *pdev)
{
	struct usnic_fwd_dev *ufdev;

	ufdev = kzalloc(sizeof(*ufdev), GFP_KERNEL);
	if (!ufdev)
		return NULL;

	ufdev->pdev = pdev;
	ufdev->netdev = pci_get_drvdata(pdev);
	spin_lock_init(&ufdev->lock);
	BUILD_BUG_ON(sizeof(ufdev->name) != sizeof(ufdev->netdev->name));
	strcpy(ufdev->name, ufdev->netdev->name);

	return ufdev;
}