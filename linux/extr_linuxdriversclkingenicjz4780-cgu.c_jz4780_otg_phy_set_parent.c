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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CGU_REG_USBPCR1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  USBPCR1_REFCLKSEL_CORE ; 
 int /*<<< orphan*/  USBPCR1_REFCLKSEL_MASK ; 
 TYPE_1__* cgu ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int jz4780_otg_phy_set_parent(struct clk_hw *hw, u8 idx)
{
	unsigned long flags;
	u32 usbpcr1;

	if (idx > 0)
		return -EINVAL;

	spin_lock_irqsave(&cgu->lock, flags);

	usbpcr1 = readl(cgu->base + CGU_REG_USBPCR1);
	usbpcr1 &= ~USBPCR1_REFCLKSEL_MASK;
	/* we only use CLKCORE */
	usbpcr1 |= USBPCR1_REFCLKSEL_CORE;
	writel(usbpcr1, cgu->base + CGU_REG_USBPCR1);

	spin_unlock_irqrestore(&cgu->lock, flags);
	return 0;
}