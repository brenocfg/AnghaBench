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
struct hinic_wq {int /*<<< orphan*/  shadow_wqe; int /*<<< orphan*/  shadow_idx; struct hinic_hwif* hwif; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_wqes_shadow(struct hinic_wq *wq)
{
	struct hinic_hwif *hwif = wq->hwif;
	struct pci_dev *pdev = hwif->pdev;

	devm_kfree(&pdev->dev, wq->shadow_idx);
	devm_kfree(&pdev->dev, wq->shadow_wqe);
}