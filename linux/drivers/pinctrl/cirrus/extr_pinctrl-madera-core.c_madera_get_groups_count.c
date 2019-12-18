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
struct pinctrl_dev {int dummy; } ;
struct madera_pin_private {TYPE_1__* chip; } ;
struct TYPE_2__ {int n_pin_groups; int n_pins; } ;

/* Variables and functions */
 struct madera_pin_private* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int madera_get_groups_count(struct pinctrl_dev *pctldev)
{
	struct madera_pin_private *priv = pinctrl_dev_get_drvdata(pctldev);

	/* Number of alt function groups plus number of single-pin groups */
	return priv->chip->n_pin_groups + priv->chip->n_pins;
}