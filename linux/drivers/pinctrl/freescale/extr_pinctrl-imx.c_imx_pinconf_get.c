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
 int imx_pinconf_get_mmio (struct pinctrl_dev*,unsigned int,unsigned long*) ; 
 int imx_pinconf_get_scu (struct pinctrl_dev*,unsigned int,unsigned long*) ; 
 struct imx_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int imx_pinconf_get(struct pinctrl_dev *pctldev,
			   unsigned pin_id, unsigned long *config)
{
	struct imx_pinctrl *ipctl = pinctrl_dev_get_drvdata(pctldev);
	const struct imx_pinctrl_soc_info *info = ipctl->info;

	if (info->flags & IMX_USE_SCU)
		return imx_pinconf_get_scu(pctldev, pin_id, config);
	else
		return imx_pinconf_get_mmio(pctldev, pin_id, config);
}