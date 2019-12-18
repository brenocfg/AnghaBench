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
struct imgu_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  mmu; int /*<<< orphan*/  base; int /*<<< orphan*/  css; } ;

/* Variables and functions */
 int /*<<< orphan*/  imgu_css_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imgu_css_set_powerdown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_dmamap_exit (struct imgu_device*) ; 
 int /*<<< orphan*/  imgu_mmu_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_video_nodes_exit (struct imgu_device*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct imgu_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void imgu_pci_remove(struct pci_dev *pci_dev)
{
	struct imgu_device *imgu = pci_get_drvdata(pci_dev);

	pm_runtime_forbid(&pci_dev->dev);
	pm_runtime_get_noresume(&pci_dev->dev);

	imgu_video_nodes_exit(imgu);
	imgu_css_cleanup(&imgu->css);
	imgu_css_set_powerdown(&pci_dev->dev, imgu->base);
	imgu_dmamap_exit(imgu);
	imgu_mmu_exit(imgu->mmu);
	mutex_destroy(&imgu->lock);
}