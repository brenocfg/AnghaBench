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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hnae3_ae_dev {int /*<<< orphan*/  priv; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hclgevf_alloc_hdev (struct hnae3_ae_dev*) ; 
 int hclgevf_init_hdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_init_ae_dev(struct hnae3_ae_dev *ae_dev)
{
	struct pci_dev *pdev = ae_dev->pdev;
	int ret;

	ret = hclgevf_alloc_hdev(ae_dev);
	if (ret) {
		dev_err(&pdev->dev, "hclge device allocation failed\n");
		return ret;
	}

	ret = hclgevf_init_hdev(ae_dev->priv);
	if (ret)
		dev_err(&pdev->dev, "hclge device initialization failed\n");

	return ret;
}