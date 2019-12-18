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
struct ufs_hba {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ufs_hba* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufshcd_dealloc_host (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_remove (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_pci_remove(struct pci_dev *pdev)
{
	struct ufs_hba *hba = pci_get_drvdata(pdev);

	pm_runtime_forbid(&pdev->dev);
	pm_runtime_get_noresume(&pdev->dev);
	ufshcd_remove(hba);
	ufshcd_dealloc_host(hba);
}