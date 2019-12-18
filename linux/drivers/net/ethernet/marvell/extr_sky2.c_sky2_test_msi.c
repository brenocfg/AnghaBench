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
struct sky2_hw {int flags; int /*<<< orphan*/  msi_wait; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  CS_CL_SW_IRQ ; 
 int /*<<< orphan*/  CS_ST_SW_IRQ ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EOPNOTSUPP ; 
 int HZ ; 
 int SKY2_HW_USE_MSI ; 
 int /*<<< orphan*/  Y2_IS_IRQ_SW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sky2_hw*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sky2_hw*) ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_read8 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_test_intr ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sky2_test_msi(struct sky2_hw *hw)
{
	struct pci_dev *pdev = hw->pdev;
	int err;

	init_waitqueue_head(&hw->msi_wait);

	err = request_irq(pdev->irq, sky2_test_intr, 0, DRV_NAME, hw);
	if (err) {
		dev_err(&pdev->dev, "cannot assign irq %d\n", pdev->irq);
		return err;
	}

	sky2_write32(hw, B0_IMSK, Y2_IS_IRQ_SW);

	sky2_write8(hw, B0_CTST, CS_ST_SW_IRQ);
	sky2_read8(hw, B0_CTST);

	wait_event_timeout(hw->msi_wait, (hw->flags & SKY2_HW_USE_MSI), HZ/10);

	if (!(hw->flags & SKY2_HW_USE_MSI)) {
		/* MSI test failed, go back to INTx mode */
		dev_info(&pdev->dev, "No interrupt generated using MSI, "
			 "switching to INTx mode.\n");

		err = -EOPNOTSUPP;
		sky2_write8(hw, B0_CTST, CS_CL_SW_IRQ);
	}

	sky2_write32(hw, B0_IMSK, 0);
	sky2_read32(hw, B0_IMSK);

	free_irq(pdev->irq, hw);

	return err;
}