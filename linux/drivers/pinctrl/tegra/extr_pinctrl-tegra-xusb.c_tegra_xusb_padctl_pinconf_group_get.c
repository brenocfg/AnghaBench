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
typedef  int u32 ;
struct tegra_xusb_padctl_lane {int /*<<< orphan*/  iddq; int /*<<< orphan*/  offset; } ;
struct tegra_xusb_padctl {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct pinctrl_dev {int dummy; } ;
typedef  enum tegra_xusb_padctl_param { ____Placeholder_tegra_xusb_padctl_param } tegra_xusb_padctl_param ;
struct TYPE_2__ {struct tegra_xusb_padctl_lane* lanes; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
#define  TEGRA_XUSB_PADCTL_IDDQ 128 
 unsigned long TEGRA_XUSB_PADCTL_PACK (int,int) ; 
 int TEGRA_XUSB_PADCTL_UNPACK_PARAM (unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int padctl_readl (struct tegra_xusb_padctl*,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_padctl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int tegra_xusb_padctl_pinconf_group_get(struct pinctrl_dev *pinctrl,
					       unsigned int group,
					       unsigned long *config)
{
	struct tegra_xusb_padctl *padctl = pinctrl_dev_get_drvdata(pinctrl);
	const struct tegra_xusb_padctl_lane *lane;
	enum tegra_xusb_padctl_param param;
	u32 value;

	param = TEGRA_XUSB_PADCTL_UNPACK_PARAM(*config);
	lane = &padctl->soc->lanes[group];

	switch (param) {
	case TEGRA_XUSB_PADCTL_IDDQ:
		/* lanes with iddq == 0 don't support this parameter */
		if (lane->iddq == 0)
			return -EINVAL;

		value = padctl_readl(padctl, lane->offset);

		if (value & BIT(lane->iddq))
			value = 0;
		else
			value = 1;

		*config = TEGRA_XUSB_PADCTL_PACK(param, value);
		break;

	default:
		dev_err(padctl->dev, "invalid configuration parameter: %04x\n",
			param);
		return -ENOTSUPP;
	}

	return 0;
}