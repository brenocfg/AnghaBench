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
struct property {int dummy; } ;
struct pinctrl_dev {TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 struct property* of_find_property (struct device_node*,char*,int*) ; 

bool pinctrl_dt_has_hogs(struct pinctrl_dev *pctldev)
{
	struct device_node *np;
	struct property *prop;
	int size;

	np = pctldev->dev->of_node;
	if (!np)
		return false;

	prop = of_find_property(np, "pinctrl-0", &size);

	return prop ? true : false;
}