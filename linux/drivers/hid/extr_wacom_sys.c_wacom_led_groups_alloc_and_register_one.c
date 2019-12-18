#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wacom_led {int dummy; } ;
struct TYPE_8__ {int count; TYPE_3__* groups; } ;
struct wacom {TYPE_2__ led; TYPE_1__* hdev; } ;
struct device {int dummy; } ;
struct TYPE_9__ {int count; struct device* dev; struct wacom_led* leds; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 struct wacom_led* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_close_group (struct device*,TYPE_3__*) ; 
 int /*<<< orphan*/  devres_open_group (struct device*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_release_group (struct device*,TYPE_3__*) ; 
 int /*<<< orphan*/  wacom_led_groups_release_one ; 
 int wacom_led_register_one (struct device*,struct wacom*,struct wacom_led*,int,int,int) ; 

__attribute__((used)) static int wacom_led_groups_alloc_and_register_one(struct device *dev,
						   struct wacom *wacom,
						   int group_id, int count,
						   bool read_only)
{
	struct wacom_led *leds;
	int i, error;

	if (group_id >= wacom->led.count || count <= 0)
		return -EINVAL;

	if (!devres_open_group(dev, &wacom->led.groups[group_id], GFP_KERNEL))
		return -ENOMEM;

	leds = devm_kcalloc(dev, count, sizeof(struct wacom_led), GFP_KERNEL);
	if (!leds) {
		error = -ENOMEM;
		goto err;
	}

	wacom->led.groups[group_id].leds = leds;
	wacom->led.groups[group_id].count = count;

	for (i = 0; i < count; i++) {
		error = wacom_led_register_one(dev, wacom, &leds[i],
					       group_id, i, read_only);
		if (error)
			goto err;
	}

	wacom->led.groups[group_id].dev = dev;

	devres_close_group(dev, &wacom->led.groups[group_id]);

	/*
	 * There is a bug (?) in devm_led_classdev_register() in which its
	 * increments the refcount of the parent. If the parent is an input
	 * device, that means the ref count never reaches 0 when
	 * devm_input_device_release() gets called.
	 * This means that the LEDs are still there after disconnect.
	 * Manually force the release of the group so that the leds are released
	 * once we are done using them.
	 */
	error = devm_add_action_or_reset(&wacom->hdev->dev,
					 wacom_led_groups_release_one,
					 &wacom->led.groups[group_id]);
	if (error)
		return error;

	return 0;

err:
	devres_release_group(dev, &wacom->led.groups[group_id]);
	return error;
}