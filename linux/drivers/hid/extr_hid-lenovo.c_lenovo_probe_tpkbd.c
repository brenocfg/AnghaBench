#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; struct device* dev; void* brightness_set; void* brightness_get; } ;
struct lenovo_drvdata_tpkbd {int sensitivity; int press_speed; TYPE_1__ led_mute; TYPE_1__ led_micmute; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct hid_device {struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 char* dev_name (struct device*) ; 
 void* devm_kzalloc (struct device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 int /*<<< orphan*/  hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_set_drvdata (struct hid_device*,struct lenovo_drvdata_tpkbd*) ; 
 int /*<<< orphan*/  hid_validate_values (struct hid_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  hid_warn (struct hid_device*,char*,int) ; 
 int led_classdev_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  lenovo_attr_group_tpkbd ; 
 int /*<<< orphan*/  lenovo_features_set_tpkbd (struct hid_device*) ; 
 void* lenovo_led_brightness_get_tpkbd ; 
 void* lenovo_led_brightness_set_tpkbd ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 int strlen (char*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lenovo_probe_tpkbd(struct hid_device *hdev)
{
	struct device *dev = &hdev->dev;
	struct lenovo_drvdata_tpkbd *data_pointer;
	size_t name_sz = strlen(dev_name(dev)) + 16;
	char *name_mute, *name_micmute;
	int i;
	int ret;

	/*
	 * Only register extra settings against subdevice where input_mapping
	 * set drvdata to 1, i.e. the trackpoint.
	 */
	if (!hid_get_drvdata(hdev))
		return 0;

	hid_set_drvdata(hdev, NULL);

	/* Validate required reports. */
	for (i = 0; i < 4; i++) {
		if (!hid_validate_values(hdev, HID_FEATURE_REPORT, 4, i, 1))
			return -ENODEV;
	}
	if (!hid_validate_values(hdev, HID_OUTPUT_REPORT, 3, 0, 2))
		return -ENODEV;

	ret = sysfs_create_group(&hdev->dev.kobj, &lenovo_attr_group_tpkbd);
	if (ret)
		hid_warn(hdev, "Could not create sysfs group: %d\n", ret);

	data_pointer = devm_kzalloc(&hdev->dev,
				    sizeof(struct lenovo_drvdata_tpkbd),
				    GFP_KERNEL);
	if (data_pointer == NULL) {
		hid_err(hdev, "Could not allocate memory for driver data\n");
		ret = -ENOMEM;
		goto err;
	}

	// set same default values as windows driver
	data_pointer->sensitivity = 0xa0;
	data_pointer->press_speed = 0x38;

	name_mute = devm_kzalloc(&hdev->dev, name_sz, GFP_KERNEL);
	name_micmute = devm_kzalloc(&hdev->dev, name_sz, GFP_KERNEL);
	if (name_mute == NULL || name_micmute == NULL) {
		hid_err(hdev, "Could not allocate memory for led data\n");
		ret = -ENOMEM;
		goto err;
	}
	snprintf(name_mute, name_sz, "%s:amber:mute", dev_name(dev));
	snprintf(name_micmute, name_sz, "%s:amber:micmute", dev_name(dev));

	hid_set_drvdata(hdev, data_pointer);

	data_pointer->led_mute.name = name_mute;
	data_pointer->led_mute.brightness_get = lenovo_led_brightness_get_tpkbd;
	data_pointer->led_mute.brightness_set = lenovo_led_brightness_set_tpkbd;
	data_pointer->led_mute.dev = dev;
	ret = led_classdev_register(dev, &data_pointer->led_mute);
	if (ret < 0)
		goto err;

	data_pointer->led_micmute.name = name_micmute;
	data_pointer->led_micmute.brightness_get =
		lenovo_led_brightness_get_tpkbd;
	data_pointer->led_micmute.brightness_set =
		lenovo_led_brightness_set_tpkbd;
	data_pointer->led_micmute.dev = dev;
	ret = led_classdev_register(dev, &data_pointer->led_micmute);
	if (ret < 0) {
		led_classdev_unregister(&data_pointer->led_mute);
		goto err;
	}

	lenovo_features_set_tpkbd(hdev);

	return 0;
err:
	sysfs_remove_group(&hdev->dev.kobj, &lenovo_attr_group_tpkbd);
	return ret;
}