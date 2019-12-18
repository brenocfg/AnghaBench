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
struct isst_if_device {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISST_IF_DEV_MBOX ; 
 int /*<<< orphan*/  isst_if_cdev_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct isst_if_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void isst_if_remove(struct pci_dev *pdev)
{
	struct isst_if_device *punit_dev;

	punit_dev = pci_get_drvdata(pdev);
	isst_if_cdev_unregister(ISST_IF_DEV_MBOX);
	mutex_destroy(&punit_dev->mutex);
}