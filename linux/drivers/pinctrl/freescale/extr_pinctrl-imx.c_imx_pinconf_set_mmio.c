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
typedef  unsigned long u32 ;
struct pinctrl_dev {int dummy; } ;
struct imx_pinctrl_soc_info {int flags; unsigned long mux_mask; TYPE_1__* pins; } ;
struct imx_pinctrl {int base; int /*<<< orphan*/  dev; struct imx_pin_reg* pin_regs; struct imx_pinctrl_soc_info* info; } ;
struct imx_pin_reg {int conf_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int SHARE_MUX_CONF_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct imx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 unsigned long readl (int) ; 
 int /*<<< orphan*/  writel (unsigned long,int) ; 

__attribute__((used)) static int imx_pinconf_set_mmio(struct pinctrl_dev *pctldev,
				unsigned pin_id, unsigned long *configs,
				unsigned num_configs)
{
	struct imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	const struct imx_pinctrl_soc_info *info = ipctl->info;
	const struct imx_pin_reg *pin_reg = &ipctl->pin_regs[pin_id];
	int i;

	if (pin_reg->conf_reg == -1) {
		dev_err(ipctl->dev, "Pin(%s) does not support config function\n",
			info->pins[pin_id].name);
		return -EINVAL;
	}

	dev_dbg(ipctl->dev, "pinconf set pin %s\n",
		info->pins[pin_id].name);

	for (i = 0; i < num_configs; i++) {
		if (info->flags & SHARE_MUX_CONF_REG) {
			u32 reg;
			reg = readl(ipctl->base + pin_reg->conf_reg);
			reg &= info->mux_mask;
			reg |= configs[i];
			writel(reg, ipctl->base + pin_reg->conf_reg);
			dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%x\n",
				pin_reg->conf_reg, reg);
		} else {
			writel(configs[i], ipctl->base + pin_reg->conf_reg);
			dev_dbg(ipctl->dev, "write: offset 0x%x val 0x%lx\n",
				pin_reg->conf_reg, configs[i]);
		}
	} /* for each config */

	return 0;
}