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
struct gem {int swrst_base; scalar_t__ phy_type; int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ GREG_IMASK ; 
 scalar_t__ GREG_SWRST ; 
 int GREG_SWRST_RXRST ; 
 int GREG_SWRST_TXRST ; 
 int STOP_TRIES ; 
 int /*<<< orphan*/  gem_pcs_reinit_adv (struct gem*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ phy_serdes ; 
 scalar_t__ phy_serialink ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gem_reset(struct gem *gp)
{
	int limit;
	u32 val;

	/* Make sure we won't get any more interrupts */
	writel(0xffffffff, gp->regs + GREG_IMASK);

	/* Reset the chip */
	writel(gp->swrst_base | GREG_SWRST_TXRST | GREG_SWRST_RXRST,
	       gp->regs + GREG_SWRST);

	limit = STOP_TRIES;

	do {
		udelay(20);
		val = readl(gp->regs + GREG_SWRST);
		if (limit-- <= 0)
			break;
	} while (val & (GREG_SWRST_TXRST | GREG_SWRST_RXRST));

	if (limit < 0)
		netdev_err(gp->dev, "SW reset is ghetto\n");

	if (gp->phy_type == phy_serialink || gp->phy_type == phy_serdes)
		gem_pcs_reinit_adv(gp);
}