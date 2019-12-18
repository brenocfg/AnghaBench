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
struct picolcd_data {struct led_classdev** led; TYPE_1__* hdev; } ;
struct led_classdev {char* name; int max_brightness; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  brightness_get; scalar_t__ brightness; } ;
struct hid_report {int maxfield; TYPE_2__** field; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int report_count; int report_size; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  kfree (struct led_classdev*) ; 
 struct led_classdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int led_classdev_register (struct device*,struct led_classdev*) ; 
 int /*<<< orphan*/  led_classdev_unregister (struct led_classdev*) ; 
 int /*<<< orphan*/  picolcd_led_get_brightness ; 
 int /*<<< orphan*/  picolcd_led_set_brightness ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int) ; 
 int strlen (char*) ; 

int picolcd_init_leds(struct picolcd_data *data, struct hid_report *report)
{
	struct device *dev = &data->hdev->dev;
	struct led_classdev *led;
	size_t name_sz = strlen(dev_name(dev)) + 8;
	char *name;
	int i, ret = 0;

	if (!report)
		return -ENODEV;
	if (report->maxfield != 1 || report->field[0]->report_count != 1 ||
			report->field[0]->report_size != 8) {
		dev_err(dev, "unsupported LED_STATE report");
		return -EINVAL;
	}

	for (i = 0; i < 8; i++) {
		led = kzalloc(sizeof(struct led_classdev)+name_sz, GFP_KERNEL);
		if (!led) {
			dev_err(dev, "can't allocate memory for LED %d\n", i);
			ret = -ENOMEM;
			goto err;
		}
		name = (void *)(&led[1]);
		snprintf(name, name_sz, "%s::GPO%d", dev_name(dev), i);
		led->name = name;
		led->brightness = 0;
		led->max_brightness = 1;
		led->brightness_get = picolcd_led_get_brightness;
		led->brightness_set = picolcd_led_set_brightness;

		data->led[i] = led;
		ret = led_classdev_register(dev, data->led[i]);
		if (ret) {
			data->led[i] = NULL;
			kfree(led);
			dev_err(dev, "can't register LED %d\n", i);
			goto err;
		}
	}
	return 0;
err:
	for (i = 0; i < 8; i++)
		if (data->led[i]) {
			led = data->led[i];
			data->led[i] = NULL;
			led_classdev_unregister(led);
			kfree(led);
		}
	return ret;
}