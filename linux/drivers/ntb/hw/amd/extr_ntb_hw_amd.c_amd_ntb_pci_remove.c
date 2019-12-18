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
struct pci_dev {int dummy; } ;
struct amd_ntb_dev {int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_deinit_dev (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  amd_deinit_side_info (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  amd_ntb_deinit_pci (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  kfree (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  ndev_deinit_debugfs (struct amd_ntb_dev*) ; 
 int /*<<< orphan*/  ntb_unregister_device (int /*<<< orphan*/ *) ; 
 struct amd_ntb_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void amd_ntb_pci_remove(struct pci_dev *pdev)
{
	struct amd_ntb_dev *ndev = pci_get_drvdata(pdev);

	ntb_unregister_device(&ndev->ntb);
	ndev_deinit_debugfs(ndev);
	amd_deinit_side_info(ndev);
	amd_deinit_dev(ndev);
	amd_ntb_deinit_pci(ndev);
	kfree(ndev);
}