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
typedef  scalar_t__ u16 ;
struct sky2_hw {TYPE_1__* pdev; struct net_device** dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMU_CLR_IRQ_CHK ; 
 int /*<<< orphan*/  PREF_UNIT_GET_IDX ; 
 int /*<<< orphan*/  PREF_UNIT_PUT_IDX ; 
 int /*<<< orphan*/  Q_ADDR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 int /*<<< orphan*/  Y2_QADDR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ sky2_read16 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_le_error(struct sky2_hw *hw, unsigned port, u16 q)
{
	struct net_device *dev = hw->dev[port];
	u16 idx = sky2_read16(hw, Y2_QADDR(q, PREF_UNIT_GET_IDX));

	dev_err(&hw->pdev->dev, "%s: descriptor error q=%#x get=%u put=%u\n",
		dev->name, (unsigned) q, (unsigned) idx,
		(unsigned) sky2_read16(hw, Y2_QADDR(q, PREF_UNIT_PUT_IDX)));

	sky2_write32(hw, Q_ADDR(q, Q_CSR), BMU_CLR_IRQ_CHK);
}