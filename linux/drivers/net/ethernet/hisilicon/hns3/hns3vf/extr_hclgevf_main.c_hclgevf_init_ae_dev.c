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
struct hnae3_ae_dev {struct hclgevf_dev* priv; struct pci_dev* pdev; } ;
struct hclgevf_dev {int /*<<< orphan*/  keep_alive_task; int /*<<< orphan*/  keep_alive_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hclgevf_alloc_hdev (struct hnae3_ae_dev*) ; 
 int hclgevf_init_hdev (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_keep_alive_task ; 
 int /*<<< orphan*/  hclgevf_keep_alive_timer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclgevf_init_ae_dev(struct hnae3_ae_dev *ae_dev)
{
	struct pci_dev *pdev = ae_dev->pdev;
	struct hclgevf_dev *hdev;
	int ret;

	ret = hclgevf_alloc_hdev(ae_dev);
	if (ret) {
		dev_err(&pdev->dev, "hclge device allocation failed\n");
		return ret;
	}

	ret = hclgevf_init_hdev(ae_dev->priv);
	if (ret) {
		dev_err(&pdev->dev, "hclge device initialization failed\n");
		return ret;
	}

	hdev = ae_dev->priv;
	timer_setup(&hdev->keep_alive_timer, hclgevf_keep_alive_timer, 0);
	INIT_WORK(&hdev->keep_alive_task, hclgevf_keep_alive_task);

	return 0;
}