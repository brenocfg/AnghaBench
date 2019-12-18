#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct madera_pin_private {TYPE_2__* chip; } ;
struct TYPE_4__ {unsigned int n_pin_groups; TYPE_1__* pin_groups; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 char const** madera_pin_single_group_names ; 
 struct madera_pin_private* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static const char *madera_get_group_name(struct pinctrl_dev *pctldev,
					 unsigned int selector)
{
	struct madera_pin_private *priv = pinctrl_dev_get_drvdata(pctldev);

	if (selector < priv->chip->n_pin_groups)
		return priv->chip->pin_groups[selector].name;

	selector -= priv->chip->n_pin_groups;
	return madera_pin_single_group_names[selector];
}