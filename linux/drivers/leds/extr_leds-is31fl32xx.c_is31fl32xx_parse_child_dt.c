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
typedef  int u32 ;
struct led_classdev {int /*<<< orphan*/  brightness_set_blocking; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct is31fl32xx_led_data {int channel; TYPE_2__* priv; struct led_classdev cdev; } ;
struct device_node {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cdef; } ;
struct TYPE_3__ {int channels; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device const*,char*,struct device_node const*) ; 
 int /*<<< orphan*/  is31fl32xx_brightness_set ; 
 scalar_t__ of_property_read_string (struct device_node const*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node const*,char*,int*) ; 

__attribute__((used)) static int is31fl32xx_parse_child_dt(const struct device *dev,
				     const struct device_node *child,
				     struct is31fl32xx_led_data *led_data)
{
	struct led_classdev *cdev = &led_data->cdev;
	int ret = 0;
	u32 reg;

	if (of_property_read_string(child, "label", &cdev->name))
		cdev->name = child->name;

	ret = of_property_read_u32(child, "reg", &reg);
	if (ret || reg < 1 || reg > led_data->priv->cdef->channels) {
		dev_err(dev,
			"Child node %pOF does not have a valid reg property\n",
			child);
		return -EINVAL;
	}
	led_data->channel = reg;

	of_property_read_string(child, "linux,default-trigger",
				&cdev->default_trigger);

	cdev->brightness_set_blocking = is31fl32xx_brightness_set;

	return 0;
}