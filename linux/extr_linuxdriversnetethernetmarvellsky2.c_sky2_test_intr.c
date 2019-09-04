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
typedef  int u32 ;
struct sky2_hw {int /*<<< orphan*/  msi_wait; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B0_Y2_SP_ICR ; 
 int /*<<< orphan*/  B0_Y2_SP_ISRC2 ; 
 int /*<<< orphan*/  CS_CL_SW_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SKY2_HW_USE_MSI ; 
 int Y2_IS_IRQ_SW ; 
 int sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sky2_test_intr(int irq, void *dev_id)
{
	struct sky2_hw *hw = dev_id;
	u32 status = sky2_read32(hw, B0_Y2_SP_ISRC2);

	if (status == 0)
		return IRQ_NONE;

	if (status & Y2_IS_IRQ_SW) {
		hw->flags |= SKY2_HW_USE_MSI;
		wake_up(&hw->msi_wait);
		sky2_write8(hw, B0_CTST, CS_CL_SW_IRQ);
	}
	sky2_write32(hw, B0_Y2_SP_ICR, 2);

	return IRQ_HANDLED;
}