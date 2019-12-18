#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  devt; } ;
struct switchtec_dev {TYPE_1__ dev; int /*<<< orphan*/  cdev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct switchtec_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  stdev_kill (struct switchtec_dev*) ; 
 int /*<<< orphan*/  switchtec_minor_ida ; 

__attribute__((used)) static void switchtec_pci_remove(struct pci_dev *pdev)
{
	struct switchtec_dev *stdev = pci_get_drvdata(pdev);

	pci_set_drvdata(pdev, NULL);

	cdev_device_del(&stdev->cdev, &stdev->dev);
	ida_simple_remove(&switchtec_minor_ida, MINOR(stdev->dev.devt));
	dev_info(&stdev->dev, "unregistered.\n");
	stdev_kill(stdev);
	put_device(&stdev->dev);
}