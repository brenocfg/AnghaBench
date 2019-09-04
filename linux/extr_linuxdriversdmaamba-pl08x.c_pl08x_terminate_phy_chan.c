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
struct pl08x_phy_chan {scalar_t__ id; scalar_t__ reg_config; scalar_t__ reg_control; scalar_t__ ftdmac020; } ;
struct pl08x_driver_data {scalar_t__ base; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int FTDMAC020_CH_CFG_INT_ABT_MASK ; 
 int FTDMAC020_CH_CFG_INT_ERR_MASK ; 
 int FTDMAC020_CH_CFG_INT_TC_MASK ; 
 int FTDMAC020_CH_CSR_ABT ; 
 int FTDMAC020_CH_CSR_EN ; 
 int PL080_CONFIG_ENABLE ; 
 int PL080_CONFIG_ERR_IRQ_MASK ; 
 int PL080_CONFIG_TC_IRQ_MASK ; 
 scalar_t__ PL080_ERR_CLEAR ; 
 scalar_t__ PL080_TC_CLEAR ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void pl08x_terminate_phy_chan(struct pl08x_driver_data *pl08x,
	struct pl08x_phy_chan *ch)
{
	u32 val;

	/* The layout for the FTDMAC020 is different */
	if (ch->ftdmac020) {
		/* Disable all interrupts */
		val = readl(ch->reg_config);
		val |= (FTDMAC020_CH_CFG_INT_ABT_MASK |
			FTDMAC020_CH_CFG_INT_ERR_MASK |
			FTDMAC020_CH_CFG_INT_TC_MASK);
		writel(val, ch->reg_config);

		/* Abort and disable channel */
		val = readl(ch->reg_control);
		val &= ~FTDMAC020_CH_CSR_EN;
		val |= FTDMAC020_CH_CSR_ABT;
		writel(val, ch->reg_control);

		/* Clear ABT and ERR interrupt flags */
		writel(BIT(ch->id) | BIT(ch->id + 16),
		       pl08x->base + PL080_ERR_CLEAR);
		writel(BIT(ch->id), pl08x->base + PL080_TC_CLEAR);

		return;
	}

	val = readl(ch->reg_config);
	val &= ~(PL080_CONFIG_ENABLE | PL080_CONFIG_ERR_IRQ_MASK |
		 PL080_CONFIG_TC_IRQ_MASK);
	writel(val, ch->reg_config);

	writel(BIT(ch->id), pl08x->base + PL080_ERR_CLEAR);
	writel(BIT(ch->id), pl08x->base + PL080_TC_CLEAR);
}