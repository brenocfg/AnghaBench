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
struct qed_dev {scalar_t__ regview; scalar_t__ doorbells; scalar_t__ db_size; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  enable_cnt; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void qed_free_pci(struct qed_dev *cdev)
{
	struct pci_dev *pdev = cdev->pdev;

	if (cdev->doorbells && cdev->db_size)
		iounmap(cdev->doorbells);
	if (cdev->regview)
		iounmap(cdev->regview);
	if (atomic_read(&pdev->enable_cnt) == 1)
		pci_release_regions(pdev);

	pci_disable_device(pdev);
}