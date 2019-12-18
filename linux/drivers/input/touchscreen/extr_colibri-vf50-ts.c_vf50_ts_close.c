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
struct vf50_touch_device {int stop_touchscreen; int /*<<< orphan*/  gpio_ym; int /*<<< orphan*/  pen_irq; TYPE_1__* pdev; } ;
struct input_dev {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vf50_touch_device* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (struct device*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vf50_ts_close(struct input_dev *dev_input)
{
	struct vf50_touch_device *touchdev = input_get_drvdata(dev_input);
	struct device *dev = &touchdev->pdev->dev;

	touchdev->stop_touchscreen = true;

	/* Make sure IRQ is not running past close */
	mb();
	synchronize_irq(touchdev->pen_irq);

	gpiod_set_value(touchdev->gpio_ym, 0);
	pinctrl_pm_select_default_state(dev);

	dev_dbg(dev, "Input device %s closed, disable touch detection\n",
		dev_input->name);
}