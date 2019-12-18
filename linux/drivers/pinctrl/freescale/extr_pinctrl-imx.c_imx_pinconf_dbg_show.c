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
struct seq_file {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct imx_pinctrl_soc_info {int flags; } ;
struct imx_pinctrl {scalar_t__ base; struct imx_pin_reg* pin_regs; int /*<<< orphan*/  dev; struct imx_pinctrl_soc_info* info; } ;
struct imx_pin_reg {int conf_reg; } ;

/* Variables and functions */
 int IMX_USE_SCU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int imx_pinconf_get_scu (struct pinctrl_dev*,unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  pin_get_name (struct pinctrl_dev*,unsigned int) ; 
 struct imx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void imx_pinconf_dbg_show(struct pinctrl_dev *pctldev,
				   struct seq_file *s, unsigned pin_id)
{
	struct imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	const struct imx_pinctrl_soc_info *info = ipctl->info;
	const struct imx_pin_reg *pin_reg;
	unsigned long config;
	int ret;

	if (info->flags & IMX_USE_SCU) {
		ret = imx_pinconf_get_scu(pctldev, pin_id, &config);
		if (ret) {
			dev_err(ipctl->dev, "failed to get %s pinconf\n",
				pin_get_name(pctldev, pin_id));
			seq_puts(s, "N/A");
			return;
		}
	} else {
		pin_reg = &ipctl->pin_regs[pin_id];
		if (pin_reg->conf_reg == -1) {
			seq_puts(s, "N/A");
			return;
		}

		config = readl(ipctl->base + pin_reg->conf_reg);
	}

	seq_printf(s, "0x%lx", config);
}