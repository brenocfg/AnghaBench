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
struct rvu {struct rvu* hw; int /*<<< orphan*/  afpf_wq_info; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct rvu*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct rvu* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvu_cgx_exit (struct rvu*) ; 
 int /*<<< orphan*/  rvu_disable_sriov (struct rvu*) ; 
 int /*<<< orphan*/  rvu_flr_wq_destroy (struct rvu*) ; 
 int /*<<< orphan*/  rvu_free_hw_resources (struct rvu*) ; 
 int /*<<< orphan*/  rvu_mbox_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvu_reset_all_blocks (struct rvu*) ; 
 int /*<<< orphan*/  rvu_unregister_interrupts (struct rvu*) ; 

__attribute__((used)) static void rvu_remove(struct pci_dev *pdev)
{
	struct rvu *rvu = pci_get_drvdata(pdev);

	rvu_unregister_interrupts(rvu);
	rvu_flr_wq_destroy(rvu);
	rvu_cgx_exit(rvu);
	rvu_mbox_destroy(&rvu->afpf_wq_info);
	rvu_disable_sriov(rvu);
	rvu_reset_all_blocks(rvu);
	rvu_free_hw_resources(rvu);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

	devm_kfree(&pdev->dev, rvu->hw);
	devm_kfree(&pdev->dev, rvu);
}