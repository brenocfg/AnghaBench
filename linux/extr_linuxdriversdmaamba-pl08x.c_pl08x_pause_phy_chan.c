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
typedef  int /*<<< orphan*/  u32 ;
struct pl08x_phy_chan {int /*<<< orphan*/  id; int /*<<< orphan*/  reg_config; int /*<<< orphan*/  reg_control; scalar_t__ ftdmac020; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTDMAC020_CH_CSR_EN ; 
 int /*<<< orphan*/  PL080_CONFIG_HALT ; 
 scalar_t__ pl08x_phy_channel_busy (struct pl08x_phy_chan*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pl08x_pause_phy_chan(struct pl08x_phy_chan *ch)
{
	u32 val;
	int timeout;

	if (ch->ftdmac020) {
		/* Use the enable bit on the FTDMAC020 */
		val = readl(ch->reg_control);
		val &= ~FTDMAC020_CH_CSR_EN;
		writel(val, ch->reg_control);
		return;
	}

	/* Set the HALT bit and wait for the FIFO to drain */
	val = readl(ch->reg_config);
	val |= PL080_CONFIG_HALT;
	writel(val, ch->reg_config);

	/* Wait for channel inactive */
	for (timeout = 1000; timeout; timeout--) {
		if (!pl08x_phy_channel_busy(ch))
			break;
		udelay(1);
	}
	if (pl08x_phy_channel_busy(ch))
		pr_err("pl08x: channel%u timeout waiting for pause\n", ch->id);
}