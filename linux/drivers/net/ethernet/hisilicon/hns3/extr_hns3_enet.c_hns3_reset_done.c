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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hnae3_ae_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flr_done ) (struct hnae3_ae_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct hnae3_ae_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_ae_dev*) ; 

__attribute__((used)) static void hns3_reset_done(struct pci_dev *pdev)
{
	struct hnae3_ae_dev *ae_dev = pci_get_drvdata(pdev);

	dev_info(&pdev->dev, "hns3 flr done\n");
	if (ae_dev && ae_dev->ops && ae_dev->ops->flr_done)
		ae_dev->ops->flr_done(ae_dev);
}