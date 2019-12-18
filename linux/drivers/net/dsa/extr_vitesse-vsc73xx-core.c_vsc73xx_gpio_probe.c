#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ngpio; int base; int can_sleep; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  of_node; TYPE_1__* parent; int /*<<< orphan*/  owner; int /*<<< orphan*/  label; } ;
struct vsc73xx {TYPE_1__* dev; TYPE_3__ gc; int /*<<< orphan*/  chipid; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int devm_gpiochip_add_data (TYPE_1__*,TYPE_3__*,struct vsc73xx*) ; 
 int /*<<< orphan*/  devm_kasprintf (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsc73xx_gpio_direction_input ; 
 int /*<<< orphan*/  vsc73xx_gpio_direction_output ; 
 int /*<<< orphan*/  vsc73xx_gpio_get ; 
 int /*<<< orphan*/  vsc73xx_gpio_get_direction ; 
 int /*<<< orphan*/  vsc73xx_gpio_set ; 

__attribute__((used)) static int vsc73xx_gpio_probe(struct vsc73xx *vsc)
{
	int ret;

	vsc->gc.label = devm_kasprintf(vsc->dev, GFP_KERNEL, "VSC%04x",
				       vsc->chipid);
	vsc->gc.ngpio = 4;
	vsc->gc.owner = THIS_MODULE;
	vsc->gc.parent = vsc->dev;
	vsc->gc.of_node = vsc->dev->of_node;
	vsc->gc.base = -1;
	vsc->gc.get = vsc73xx_gpio_get;
	vsc->gc.set = vsc73xx_gpio_set;
	vsc->gc.direction_input = vsc73xx_gpio_direction_input;
	vsc->gc.direction_output = vsc73xx_gpio_direction_output;
	vsc->gc.get_direction = vsc73xx_gpio_get_direction;
	vsc->gc.can_sleep = true;
	ret = devm_gpiochip_add_data(vsc->dev, &vsc->gc, vsc);
	if (ret) {
		dev_err(vsc->dev, "unable to register GPIO chip\n");
		return ret;
	}
	return 0;
}