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
struct TYPE_2__ {int priority; int /*<<< orphan*/  notifier_call; } ;
struct rave_sp_power_button {TYPE_1__ nb; struct input_dev* idev; } ;
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct input_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KEY_POWER ; 
 struct input_dev* devm_input_allocate_device (struct device*) ; 
 struct rave_sp_power_button* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_rave_sp_register_event_notifier (struct device*,TYPE_1__*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_set_capability (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rave_sp_power_button_event ; 

__attribute__((used)) static int rave_sp_pwrbutton_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rave_sp_power_button *pb;
	struct input_dev *idev;
	int error;

	pb = devm_kzalloc(dev, sizeof(*pb), GFP_KERNEL);
	if (!pb)
		return -ENOMEM;

	idev = devm_input_allocate_device(dev);
	if (!idev)
		return -ENOMEM;

	idev->name = pdev->name;

	input_set_capability(idev, EV_KEY, KEY_POWER);

	error = input_register_device(idev);
	if (error)
		return error;

	pb->idev = idev;
	pb->nb.notifier_call = rave_sp_power_button_event;
	pb->nb.priority = 128;

	error = devm_rave_sp_register_event_notifier(dev, &pb->nb);
	if (error)
		return error;

	return 0;
}