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
struct pinctrl_dev {int dummy; } ;
struct imx_pinctrl_soc_info {int flags; } ;
struct imx_pinctrl {struct imx_pinctrl_soc_info* info; } ;

/* Variables and functions */
 int IMX_USE_SCU ; 
 int imx_pinconf_set_mmio (struct pinctrl_dev*,unsigned int,unsigned long*,unsigned int) ; 
 int imx_pinconf_set_scu (struct pinctrl_dev*,unsigned int,unsigned long*,unsigned int) ; 
 struct imx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int imx_pinconf_set(struct pinctrl_dev *pctldev,
			   unsigned pin_id, unsigned long *configs,
			   unsigned num_configs)
{
	struct imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	const struct imx_pinctrl_soc_info *info = ipctl->info;

	if (info->flags & IMX_USE_SCU)
		return imx_pinconf_set_scu(pctldev, pin_id,
					   configs, num_configs);
	else
		return imx_pinconf_set_mmio(pctldev, pin_id,
					    configs, num_configs);
}