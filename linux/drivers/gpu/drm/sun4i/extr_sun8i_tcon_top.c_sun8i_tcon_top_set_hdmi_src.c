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
 scalar_t__ TCON_TOP_GATE_SRC_REG ; 
 int /*<<< orphan*/  TCON_TOP_HDMI_SRC_MSK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sun8i_tcon_top* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sun8i_tcon_top_node_is_tcon_top (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int sun8i_tcon_top_set_hdmi_src(struct device *dev, int tcon)
{
	struct sun8i_tcon_top *tcon_top = dev_get_drvdata(dev);
	unsigned long flags;
	u32 val;

	if (!sun8i_tcon_top_node_is_tcon_top(dev->of_node)) {
		dev_err(dev, "Device is not TCON TOP!\n");
		return -EINVAL;
	}

	if (tcon < 2 || tcon > 3) {
		dev_err(dev, "TCON index must be 2 or 3!\n");
		return -EINVAL;
	}

	spin_lock_irqsave(&tcon_top->reg_lock, flags);

	val = readl(tcon_top->regs + TCON_TOP_GATE_SRC_REG);
	val &= ~TCON_TOP_HDMI_SRC_MSK;
	val |= FIELD_PREP(TCON_TOP_HDMI_SRC_MSK, tcon - 1);
	writel(val, tcon_top->regs + TCON_TOP_GATE_SRC_REG);

	spin_unlock_irqrestore(&tcon_top->reg_lock, flags);

	return 0;
}