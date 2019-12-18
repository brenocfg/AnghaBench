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
struct sky2_hw {int flags; int /*<<< orphan*/  napi; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int SKY2_HW_IRQ_SETUP ; 
 int SKY2_HW_USE_MSI ; 
 int /*<<< orphan*/  Y2_IS_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct sky2_hw*) ; 
 int /*<<< orphan*/  sky2_intr ; 
 int /*<<< orphan*/  sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_setup_irq(struct sky2_hw *hw, const char *name)
{
	struct pci_dev *pdev = hw->pdev;
	int err;

	err = request_irq(pdev->irq, sky2_intr,
			  (hw->flags & SKY2_HW_USE_MSI) ? 0 : IRQF_SHARED,
			  name, hw);
	if (err)
		dev_err(&pdev->dev, "cannot assign irq %d\n", pdev->irq);
	else {
		hw->flags |= SKY2_HW_IRQ_SETUP;

		napi_enable(&hw->napi);
		sky2_write32(hw, B0_IMSK, Y2_IS_BASE);
		sky2_read32(hw, B0_IMSK);
	}

	return err;
}