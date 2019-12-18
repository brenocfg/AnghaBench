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
struct amd_mp2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_mp2_clear_reg (struct amd_mp2_dev*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 struct amd_mp2_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_intx (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_forbid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amd_mp2_pci_remove(struct pci_dev *pci_dev)
{
	struct amd_mp2_dev *privdata = pci_get_drvdata(pci_dev);

	pm_runtime_forbid(&pci_dev->dev);
	pm_runtime_get_noresume(&pci_dev->dev);

	pci_intx(pci_dev, 0);
	pci_clear_master(pci_dev);

	amd_mp2_clear_reg(privdata);
}