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
struct lg_drv_data {struct lg4ff_device_entry* device_props; } ;
struct TYPE_2__ {struct lg4ff_device_entry** led; scalar_t__ alternate_modes; } ;
struct lg4ff_device_entry {TYPE_1__ wdata; } ;
struct led_classdev {TYPE_1__ wdata; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_hid (char*) ; 
 int /*<<< orphan*/  dev_attr_alternate_modes ; 
 int /*<<< orphan*/  dev_attr_combine_pedals ; 
 int /*<<< orphan*/  dev_attr_range ; 
 int /*<<< orphan*/  dev_attr_real_id ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*) ; 
 struct lg_drv_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (struct lg4ff_device_entry*) ; 
 int /*<<< orphan*/  led_classdev_unregister (struct lg4ff_device_entry*) ; 

int lg4ff_deinit(struct hid_device *hid)
{
	struct lg4ff_device_entry *entry;
	struct lg_drv_data *drv_data;

	drv_data = hid_get_drvdata(hid);
	if (!drv_data) {
		hid_err(hid, "Error while deinitializing device, no private driver data.\n");
		return -1;
	}
	entry = drv_data->device_props;
	if (!entry)
		goto out; /* Nothing more to do */

	/* Multimode devices will have at least the "MODE_NATIVE" bit set */
	if (entry->wdata.alternate_modes) {
		device_remove_file(&hid->dev, &dev_attr_real_id);
		device_remove_file(&hid->dev, &dev_attr_alternate_modes);
	}

	device_remove_file(&hid->dev, &dev_attr_combine_pedals);
	device_remove_file(&hid->dev, &dev_attr_range);
#ifdef CONFIG_LEDS_CLASS
	{
		int j;
		struct led_classdev *led;

		/* Deregister LEDs (if any) */
		for (j = 0; j < 5; j++) {

			led = entry->wdata.led[j];
			entry->wdata.led[j] = NULL;
			if (!led)
				continue;
			led_classdev_unregister(led);
			kfree(led);
		}
	}
#endif
	drv_data->device_props = NULL;

	kfree(entry);
out:
	dbg_hid("Device successfully unregistered\n");
	return 0;
}