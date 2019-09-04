#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct ice_pf {int num_alloc_vsi; int /*<<< orphan*/  hw; TYPE_1__* pdev; int /*<<< orphan*/ * vsi; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  ice_clear_interrupt_scheme (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_deinit_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_deinit_pf (struct ice_pf*) ; 
 int /*<<< orphan*/  ice_free_irq_msix_misc (struct ice_pf*) ; 
 int ice_vsi_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct ice_pf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_remove(struct pci_dev *pdev)
{
	struct ice_pf *pf = pci_get_drvdata(pdev);
	int i = 0;
	int err;

	if (!pf)
		return;

	set_bit(__ICE_DOWN, pf->state);

	for (i = 0; i < pf->num_alloc_vsi; i++) {
		if (!pf->vsi[i])
			continue;

		err = ice_vsi_release(pf->vsi[i]);
		if (err)
			dev_dbg(&pf->pdev->dev, "Failed to release VSI index %d (err %d)\n",
				i, err);
	}

	ice_free_irq_msix_misc(pf);
	ice_clear_interrupt_scheme(pf);
	ice_deinit_pf(pf);
	ice_deinit_hw(&pf->hw);
	pci_disable_pcie_error_reporting(pdev);
}