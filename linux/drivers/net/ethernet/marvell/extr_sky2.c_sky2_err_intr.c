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
typedef  int u32 ;
struct sky2_hw {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_R1 ; 
 int /*<<< orphan*/  Q_R2 ; 
 int /*<<< orphan*/  Q_XA1 ; 
 int /*<<< orphan*/  Q_XA2 ; 
 int Y2_IS_CHK_RX1 ; 
 int Y2_IS_CHK_RX2 ; 
 int Y2_IS_CHK_TXA1 ; 
 int Y2_IS_CHK_TXA2 ; 
 int Y2_IS_HW_ERR ; 
 int Y2_IS_IRQ_MAC1 ; 
 int Y2_IS_IRQ_MAC2 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  sky2_hw_intr (struct sky2_hw*) ; 
 int /*<<< orphan*/  sky2_le_error (struct sky2_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_mac_intr (struct sky2_hw*,int) ; 

__attribute__((used)) static void sky2_err_intr(struct sky2_hw *hw, u32 status)
{
	if (net_ratelimit())
		dev_warn(&hw->pdev->dev, "error interrupt status=%#x\n", status);

	if (status & Y2_IS_HW_ERR)
		sky2_hw_intr(hw);

	if (status & Y2_IS_IRQ_MAC1)
		sky2_mac_intr(hw, 0);

	if (status & Y2_IS_IRQ_MAC2)
		sky2_mac_intr(hw, 1);

	if (status & Y2_IS_CHK_RX1)
		sky2_le_error(hw, 0, Q_R1);

	if (status & Y2_IS_CHK_RX2)
		sky2_le_error(hw, 1, Q_R2);

	if (status & Y2_IS_CHK_TXA1)
		sky2_le_error(hw, 0, Q_XA1);

	if (status & Y2_IS_CHK_TXA2)
		sky2_le_error(hw, 1, Q_XA2);
}