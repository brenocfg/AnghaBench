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
typedef  int u32 ;
struct v4l2_subdev_ops {int dummy; } ;
struct v4l2_subdev {int grp_id; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {char* name; } ;
struct cx18 {TYPE_1__ v4l2_dev; struct v4l2_subdev sd_resetctrl; struct v4l2_subdev sd_gpiomux; } ;

/* Variables and functions */
#define  CX18_HW_GPIO_MUX 129 
#define  CX18_HW_GPIO_RESET_CTRL 128 
 int EINVAL ; 
 struct v4l2_subdev_ops gpiomux_ops ; 
 struct v4l2_subdev_ops resetctrl_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int v4l2_device_register_subdev (TYPE_1__*,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct cx18*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,struct v4l2_subdev_ops const*) ; 

int cx18_gpio_register(struct cx18 *cx, u32 hw)
{
	struct v4l2_subdev *sd;
	const struct v4l2_subdev_ops *ops;
	char *str;

	switch (hw) {
	case CX18_HW_GPIO_MUX:
		sd = &cx->sd_gpiomux;
		ops = &gpiomux_ops;
		str = "gpio-mux";
		break;
	case CX18_HW_GPIO_RESET_CTRL:
		sd = &cx->sd_resetctrl;
		ops = &resetctrl_ops;
		str = "gpio-reset-ctrl";
		break;
	default:
		return -EINVAL;
	}

	v4l2_subdev_init(sd, ops);
	v4l2_set_subdevdata(sd, cx);
	snprintf(sd->name, sizeof(sd->name), "%s %s", cx->v4l2_dev.name, str);
	sd->grp_id = hw;
	return v4l2_device_register_subdev(&cx->v4l2_dev, sd);
}