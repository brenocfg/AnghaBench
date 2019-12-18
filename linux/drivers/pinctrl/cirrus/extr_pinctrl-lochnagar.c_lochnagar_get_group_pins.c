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
struct lochnagar_pin_priv {TYPE_1__* groups; } ;
struct TYPE_2__ {unsigned int* pins; unsigned int npins; } ;

/* Variables and functions */
 struct lochnagar_pin_priv* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int lochnagar_get_group_pins(struct pinctrl_dev *pctldev,
				    unsigned int group_idx,
				    const unsigned int **pins,
				    unsigned int *num_pins)
{
	struct lochnagar_pin_priv *priv = pinctrl_dev_get_drvdata(pctldev);

	*pins = priv->groups[group_idx].pins;
	*num_pins = priv->groups[group_idx].npins;

	return 0;
}