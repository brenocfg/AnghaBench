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
struct pci_device_id {int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hnae3_ae_dev {int /*<<< orphan*/  dev_type; int /*<<< orphan*/  flag; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HNAE3_DEV_KNIC ; 
 struct hnae3_ae_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hnae3_register_ae_dev (struct hnae3_ae_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct hnae3_ae_dev*) ; 

__attribute__((used)) static int hns3_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct hnae3_ae_dev *ae_dev;
	int ret;

	ae_dev = devm_kzalloc(&pdev->dev, sizeof(*ae_dev),
			      GFP_KERNEL);
	if (!ae_dev) {
		ret = -ENOMEM;
		return ret;
	}

	ae_dev->pdev = pdev;
	ae_dev->flag = ent->driver_data;
	ae_dev->dev_type = HNAE3_DEV_KNIC;
	pci_set_drvdata(pdev, ae_dev);

	hnae3_register_ae_dev(ae_dev);

	return 0;
}