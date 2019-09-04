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
struct vf50_touch_device {int stop_touchscreen; TYPE_1__* pdev; } ;
struct input_dev {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct vf50_touch_device* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  vf50_ts_enable_touch_detection (struct vf50_touch_device*) ; 

__attribute__((used)) static int vf50_ts_open(struct input_dev *dev_input)
{
	struct vf50_touch_device *touchdev = input_get_drvdata(dev_input);
	struct device *dev = &touchdev->pdev->dev;

	dev_dbg(dev, "Input device %s opened, starting touch detection\n",
		dev_input->name);

	touchdev->stop_touchscreen = false;

	/* Mux detection before request IRQ, wait for pull-up to settle */
	vf50_ts_enable_touch_detection(touchdev);

	return 0;
}