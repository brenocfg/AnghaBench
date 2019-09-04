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
struct sun8i_tcon_top {int /*<<< orphan*/  reg_lock; scalar_t__ regs; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TCON_TOP_PORT_DE0_MSK ; 
 int /*<<< orphan*/  TCON_TOP_PORT_DE1_MSK ; 
 scalar_t__ TCON_TOP_PORT_SEL_REG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sun8i_tcon_top* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sun8i_tcon_top_node_is_tcon_top (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int sun8i_tcon_top_de_config(struct device *dev, int mixer, int tcon)
{
	struct sun8i_tcon_top *tcon_top = dev_get_drvdata(dev);
	unsigned long flags;
	u32 reg;

	if (!sun8i_tcon_top_node_is_tcon_top(dev->of_node)) {
		dev_err(dev, "Device is not TCON TOP!\n");
		return -EINVAL;
	}

	if (mixer > 1) {
		dev_err(dev, "Mixer index is too high!\n");
		return -EINVAL;
	}

	if (tcon > 3) {
		dev_err(dev, "TCON index is too high!\n");
		return -EINVAL;
	}

	spin_lock_irqsave(&tcon_top->reg_lock, flags);

	reg = readl(tcon_top->regs + TCON_TOP_PORT_SEL_REG);
	if (mixer == 0) {
		reg &= ~TCON_TOP_PORT_DE0_MSK;
		reg |= FIELD_PREP(TCON_TOP_PORT_DE0_MSK, tcon);
	} else {
		reg &= ~TCON_TOP_PORT_DE1_MSK;
		reg |= FIELD_PREP(TCON_TOP_PORT_DE1_MSK, tcon);
	}
	writel(reg, tcon_top->regs + TCON_TOP_PORT_SEL_REG);

	spin_unlock_irqrestore(&tcon_top->reg_lock, flags);

	return 0;
}