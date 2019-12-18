#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct brcmstb_i2c_dev {scalar_t__ clk_freq_hz; int /*<<< orphan*/  device; TYPE_1__* bsc_regmap; } ;
struct TYPE_5__ {scalar_t__ hz; int scl_mask; int div_mask; } ;
struct TYPE_4__ {int ctl_reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int BSC_CTL_REG_DIV_CLK_MASK ; 
 int BSC_CTL_REG_SCL_SEL_MASK ; 
 int BSC_CTL_REG_SCL_SEL_SHIFT ; 
 TYPE_2__* bsc_clk ; 
 int bsc_readl (struct brcmstb_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsc_writel (struct brcmstb_i2c_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_reg ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void brcmstb_i2c_set_bus_speed(struct brcmstb_i2c_dev *dev)
{
	int i = 0, num_speeds = ARRAY_SIZE(bsc_clk);
	u32 clk_freq_hz = dev->clk_freq_hz;

	for (i = 0; i < num_speeds; i++) {
		if (bsc_clk[i].hz == clk_freq_hz) {
			dev->bsc_regmap->ctl_reg &= ~(BSC_CTL_REG_SCL_SEL_MASK
						| BSC_CTL_REG_DIV_CLK_MASK);
			dev->bsc_regmap->ctl_reg |= (bsc_clk[i].scl_mask |
						     bsc_clk[i].div_mask);
			bsc_writel(dev, dev->bsc_regmap->ctl_reg, ctl_reg);
			break;
		}
	}

	/* in case we did not get find a valid speed */
	if (i == num_speeds) {
		i = (bsc_readl(dev, ctl_reg) & BSC_CTL_REG_SCL_SEL_MASK) >>
			BSC_CTL_REG_SCL_SEL_SHIFT;
		dev_warn(dev->device, "leaving current clock-frequency @ %dHz\n",
			bsc_clk[i].hz);
	}
}