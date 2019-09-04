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
struct mem_ctl_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ amd76x_pci ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 struct mem_ctl_info* edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_pci_release_generic_ctl (scalar_t__) ; 

__attribute__((used)) static void amd76x_remove_one(struct pci_dev *pdev)
{
	struct mem_ctl_info *mci;

	edac_dbg(0, "\n");

	if (amd76x_pci)
		edac_pci_release_generic_ctl(amd76x_pci);

	if ((mci = edac_mc_del_mc(&pdev->dev)) == NULL)
		return;

	edac_mc_free(mci);
}