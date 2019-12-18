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
struct pinctrl_dev {TYPE_1__* desc; } ;
struct pinconf_ops {int (* pin_config_set ) (struct pinctrl_dev*,unsigned int,unsigned long*,size_t) ;} ;
struct TYPE_2__ {struct pinconf_ops* confops; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct pinctrl_dev*,unsigned int,unsigned long*,size_t) ; 

int pinconf_set_config(struct pinctrl_dev *pctldev, unsigned pin,
		       unsigned long *configs, size_t nconfigs)
{
	const struct pinconf_ops *ops;

	ops = pctldev->desc->confops;
	if (!ops || !ops->pin_config_set)
		return -ENOTSUPP;

	return ops->pin_config_set(pctldev, pin, configs, nconfigs);
}