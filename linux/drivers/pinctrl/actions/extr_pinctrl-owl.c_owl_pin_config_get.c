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
typedef  int /*<<< orphan*/  u32 ;
struct pinctrl_dev {int dummy; } ;
struct owl_pinctrl {TYPE_1__* soc; } ;
struct owl_padinfo {int dummy; } ;
struct TYPE_2__ {int (* padctl_val2arg ) (struct owl_padinfo const*,unsigned int,int /*<<< orphan*/ *) ;struct owl_padinfo* padinfo; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int owl_pad_pinconf_reg (struct owl_padinfo const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  owl_read_field (struct owl_pinctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long pinconf_to_config_packed (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int pinconf_to_config_param (unsigned long) ; 
 struct owl_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int stub1 (struct owl_padinfo const*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int owl_pin_config_get(struct pinctrl_dev *pctrldev,
				unsigned int pin,
				unsigned long *config)
{
	int ret = 0;
	struct owl_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctrldev);
	const struct owl_padinfo *info;
	unsigned int param = pinconf_to_config_param(*config);
	u32 reg, bit, width, arg;

	info = &pctrl->soc->padinfo[pin];

	ret = owl_pad_pinconf_reg(info, param, &reg, &bit, &width);
	if (ret)
		return ret;

	arg = owl_read_field(pctrl, reg, bit, width);

	if (!pctrl->soc->padctl_val2arg)
		return -ENOTSUPP;

	ret = pctrl->soc->padctl_val2arg(info, param, &arg);
	if (ret)
		return ret;

	*config = pinconf_to_config_packed(param, arg);

	return ret;
}