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
struct sun4i_ps2data {int /*<<< orphan*/  lock; scalar_t__ reg_base; int /*<<< orphan*/  clk; } ;
struct serio {struct sun4i_ps2data* port_data; } ;

/* Variables and functions */
 int PS2_FCTL_RXOFIEN ; 
 int PS2_FCTL_RXRDYIEN ; 
 int PS2_FCTL_RXRST ; 
 int PS2_FCTL_RXUFIEN ; 
 int PS2_FCTL_TXOFIEN ; 
 int PS2_FCTL_TXRST ; 
 int PS2_FCTL_TXUFIEN ; 
 int PS2_GCTL_BUSEN ; 
 int PS2_GCTL_INTEN ; 
 int PS2_GCTL_MASTER ; 
 int PS2_GCTL_RESET ; 
 int PS2_LCTL_ACKERREN ; 
 int PS2_LCTL_PARERREN ; 
 int PS2_LCTL_RXDTOEN ; 
 int PS2_LCTL_STOPERREN ; 
 scalar_t__ PS2_REG_CLKDR ; 
 scalar_t__ PS2_REG_FCTL ; 
 scalar_t__ PS2_REG_GCTL ; 
 scalar_t__ PS2_REG_LCTL ; 
 int PS2_SAMPLE_CLK ; 
 int PS2_SCLK ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sun4i_ps2_open(struct serio *serio)
{
	struct sun4i_ps2data *drvdata = serio->port_data;
	u32 src_clk = 0;
	u32 clk_scdf;
	u32 clk_pcdf;
	u32 rval;
	unsigned long flags;

	/* Set line control and enable interrupt */
	rval = PS2_LCTL_STOPERREN | PS2_LCTL_ACKERREN
		| PS2_LCTL_PARERREN | PS2_LCTL_RXDTOEN;
	writel(rval, drvdata->reg_base + PS2_REG_LCTL);

	/* Reset FIFO */
	rval = PS2_FCTL_TXRST | PS2_FCTL_RXRST | PS2_FCTL_TXUFIEN
		| PS2_FCTL_TXOFIEN | PS2_FCTL_RXUFIEN
		| PS2_FCTL_RXOFIEN | PS2_FCTL_RXRDYIEN;

	writel(rval, drvdata->reg_base + PS2_REG_FCTL);

	src_clk = clk_get_rate(drvdata->clk);
	/* Set clock divider register */
	clk_scdf = src_clk / PS2_SAMPLE_CLK - 1;
	clk_pcdf = PS2_SAMPLE_CLK / PS2_SCLK - 1;
	rval = (clk_scdf << 8) | clk_pcdf;
	writel(rval, drvdata->reg_base + PS2_REG_CLKDR);

	/* Set global control register */
	rval = PS2_GCTL_RESET | PS2_GCTL_INTEN | PS2_GCTL_MASTER
		| PS2_GCTL_BUSEN;

	spin_lock_irqsave(&drvdata->lock, flags);
	writel(rval, drvdata->reg_base + PS2_REG_GCTL);
	spin_unlock_irqrestore(&drvdata->lock, flags);

	return 0;
}