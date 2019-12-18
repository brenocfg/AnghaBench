#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hswc_params {int dummy; } ;
struct TYPE_7__ {char* name; int max_brightness; char* default_trigger; int /*<<< orphan*/  flags; int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  brightness_set; } ;
struct asus_wireless_data {int /*<<< orphan*/  wq; TYPE_3__ led; int /*<<< orphan*/  led_work; struct hswc_params const* hswc_params; TYPE_2__* idev; struct acpi_device* adev; } ;
struct acpi_device_id {scalar_t__ driver_data; scalar_t__* id; } ;
struct acpi_device {int /*<<< orphan*/  dev; struct asus_wireless_data* driver_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  vendor; int /*<<< orphan*/  bustype; } ;
struct TYPE_6__ {char* name; char* phys; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEY_RFKILL ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_ASUSTEK ; 
 int /*<<< orphan*/  acpi_device_hid (struct acpi_device*) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct acpi_device_id* device_ids ; 
 TYPE_2__* devm_input_allocate_device (int /*<<< orphan*/ *) ; 
 struct asus_wireless_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  led_state_get ; 
 int /*<<< orphan*/  led_state_set ; 
 int /*<<< orphan*/  led_state_update ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asus_wireless_add(struct acpi_device *adev)
{
	struct asus_wireless_data *data;
	const struct acpi_device_id *id;
	int err;

	data = devm_kzalloc(&adev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	adev->driver_data = data;
	data->adev = adev;

	data->idev = devm_input_allocate_device(&adev->dev);
	if (!data->idev)
		return -ENOMEM;
	data->idev->name = "Asus Wireless Radio Control";
	data->idev->phys = "asus-wireless/input0";
	data->idev->id.bustype = BUS_HOST;
	data->idev->id.vendor = PCI_VENDOR_ID_ASUSTEK;
	set_bit(EV_KEY, data->idev->evbit);
	set_bit(KEY_RFKILL, data->idev->keybit);
	err = input_register_device(data->idev);
	if (err)
		return err;

	for (id = device_ids; id->id[0]; id++) {
		if (!strcmp((char *) id->id, acpi_device_hid(adev))) {
			data->hswc_params =
				(const struct hswc_params *)id->driver_data;
			break;
		}
	}
	if (!data->hswc_params)
		return 0;

	data->wq = create_singlethread_workqueue("asus_wireless_workqueue");
	if (!data->wq)
		return -ENOMEM;
	INIT_WORK(&data->led_work, led_state_update);
	data->led.name = "asus-wireless::airplane";
	data->led.brightness_set = led_state_set;
	data->led.brightness_get = led_state_get;
	data->led.flags = LED_CORE_SUSPENDRESUME;
	data->led.max_brightness = 1;
	data->led.default_trigger = "rfkill-none";
	err = devm_led_classdev_register(&adev->dev, &data->led);
	if (err)
		destroy_workqueue(data->wq);

	return err;
}