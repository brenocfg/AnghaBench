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
struct cas {scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ REG_MAC_RX_RESET ; 
 scalar_t__ REG_MAC_STATE_MACHINE ; 
 scalar_t__ REG_MAC_TX_RESET ; 
 int STOP_TRIES ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cas_mac_reset(struct cas *cp)
{
	int i;

	/* do both TX and RX reset */
	writel(0x1, cp->regs + REG_MAC_TX_RESET);
	writel(0x1, cp->regs + REG_MAC_RX_RESET);

	/* wait for TX */
	i = STOP_TRIES;
	while (i-- > 0) {
		if (readl(cp->regs + REG_MAC_TX_RESET) == 0)
			break;
		udelay(10);
	}

	/* wait for RX */
	i = STOP_TRIES;
	while (i-- > 0) {
		if (readl(cp->regs + REG_MAC_RX_RESET) == 0)
			break;
		udelay(10);
	}

	if (readl(cp->regs + REG_MAC_TX_RESET) |
	    readl(cp->regs + REG_MAC_RX_RESET))
		netdev_err(cp->dev, "mac tx[%d]/rx[%d] reset failed [%08x]\n",
			   readl(cp->regs + REG_MAC_TX_RESET),
			   readl(cp->regs + REG_MAC_RX_RESET),
			   readl(cp->regs + REG_MAC_STATE_MACHINE));
}