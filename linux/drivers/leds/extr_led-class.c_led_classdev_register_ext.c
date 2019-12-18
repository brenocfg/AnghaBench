#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct led_init_data {scalar_t__ fwnode; int /*<<< orphan*/  devicename; scalar_t__ devname_mandatory; } ;
struct led_classdev {char* name; int flags; int brightness_hw_changed; int /*<<< orphan*/  led_access; scalar_t__ max_brightness; int /*<<< orphan*/  node; int /*<<< orphan*/  trigger_lock; scalar_t__ work_flags; TYPE_1__* dev; int /*<<< orphan*/  groups; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  final_name ;
struct TYPE_6__ {scalar_t__ fwnode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int LED_BRIGHT_HW_CHANGED ; 
 scalar_t__ LED_FULL ; 
 int LED_MAX_NAME_SIZE ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* device_create_with_groups (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,struct led_classdev*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int led_add_brightness_hw_changed (struct led_classdev*) ; 
 int led_classdev_next_name (char const*,char*,int) ; 
 int led_compose_name (struct device*,struct led_init_data*,char*) ; 
 int /*<<< orphan*/  led_init_core (struct led_classdev*) ; 
 int /*<<< orphan*/  led_trigger_set_default (struct led_classdev*) ; 
 int /*<<< orphan*/  led_update_brightness (struct led_classdev*) ; 
 int /*<<< orphan*/  leds_class ; 
 int /*<<< orphan*/  leds_list ; 
 int /*<<< orphan*/  leds_list_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int led_classdev_register_ext(struct device *parent,
			      struct led_classdev *led_cdev,
			      struct led_init_data *init_data)
{
	char composed_name[LED_MAX_NAME_SIZE];
	char final_name[LED_MAX_NAME_SIZE];
	const char *proposed_name = composed_name;
	int ret;

	if (init_data) {
		if (init_data->devname_mandatory && !init_data->devicename) {
			dev_err(parent, "Mandatory device name is missing");
			return -EINVAL;
		}
		ret = led_compose_name(parent, init_data, composed_name);
		if (ret < 0)
			return ret;
	} else {
		proposed_name = led_cdev->name;
	}

	ret = led_classdev_next_name(proposed_name, final_name, sizeof(final_name));
	if (ret < 0)
		return ret;

	mutex_init(&led_cdev->led_access);
	mutex_lock(&led_cdev->led_access);
	led_cdev->dev = device_create_with_groups(leds_class, parent, 0,
				led_cdev, led_cdev->groups, "%s", final_name);
	if (IS_ERR(led_cdev->dev)) {
		mutex_unlock(&led_cdev->led_access);
		return PTR_ERR(led_cdev->dev);
	}
	if (init_data && init_data->fwnode)
		led_cdev->dev->fwnode = init_data->fwnode;

	if (ret)
		dev_warn(parent, "Led %s renamed to %s due to name collision",
				led_cdev->name, dev_name(led_cdev->dev));

	if (led_cdev->flags & LED_BRIGHT_HW_CHANGED) {
		ret = led_add_brightness_hw_changed(led_cdev);
		if (ret) {
			device_unregister(led_cdev->dev);
			led_cdev->dev = NULL;
			mutex_unlock(&led_cdev->led_access);
			return ret;
		}
	}

	led_cdev->work_flags = 0;
#ifdef CONFIG_LEDS_TRIGGERS
	init_rwsem(&led_cdev->trigger_lock);
#endif
#ifdef CONFIG_LEDS_BRIGHTNESS_HW_CHANGED
	led_cdev->brightness_hw_changed = -1;
#endif
	/* add to the list of leds */
	down_write(&leds_list_lock);
	list_add_tail(&led_cdev->node, &leds_list);
	up_write(&leds_list_lock);

	if (!led_cdev->max_brightness)
		led_cdev->max_brightness = LED_FULL;

	led_update_brightness(led_cdev);

	led_init_core(led_cdev);

#ifdef CONFIG_LEDS_TRIGGERS
	led_trigger_set_default(led_cdev);
#endif

	mutex_unlock(&led_cdev->led_access);

	dev_dbg(parent, "Registered led device: %s\n",
			led_cdev->name);

	return 0;
}