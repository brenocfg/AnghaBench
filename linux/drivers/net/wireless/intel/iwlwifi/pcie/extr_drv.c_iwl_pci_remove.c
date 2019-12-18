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
struct iwl_trans {int /*<<< orphan*/  drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_drv_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_pcie_free (struct iwl_trans*) ; 
 struct iwl_trans* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void iwl_pci_remove(struct pci_dev *pdev)
{
	struct iwl_trans *trans = pci_get_drvdata(pdev);

	iwl_drv_stop(trans->drv);

	iwl_trans_pcie_free(trans);
}