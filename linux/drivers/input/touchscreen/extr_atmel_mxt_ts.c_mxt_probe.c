#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mxt_data {scalar_t__ reset_gpio; int /*<<< orphan*/  suspend_mode; int /*<<< orphan*/  crc_completion; int /*<<< orphan*/  reset_completion; int /*<<< orphan*/  bl_completion; int /*<<< orphan*/  irq; struct i2c_client* client; int /*<<< orphan*/  phys; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {int addr; TYPE_2__ dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; TYPE_1__* adapter; } ;
struct TYPE_8__ {int nr; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPANION (TYPE_2__*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  MXT_RESET_GPIO_TIME ; 
 int /*<<< orphan*/  MXT_RESET_INVALID_CHG ; 
 int /*<<< orphan*/  MXT_SUSPEND_DEEP_SLEEP ; 
 int /*<<< orphan*/  MXT_SUSPEND_T9_CTRL ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  chromebook_T9_suspend_dmi ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  device_property_present (TYPE_2__*,char*) ; 
 scalar_t__ devm_gpiod_get_optional (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct mxt_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mxt_data*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct mxt_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxt_attr_group ; 
 int /*<<< orphan*/  mxt_free_input_device (struct mxt_data*) ; 
 int /*<<< orphan*/  mxt_free_object_table (struct mxt_data*) ; 
 int mxt_initialize (struct mxt_data*) ; 
 int /*<<< orphan*/  mxt_interrupt ; 
 int mxt_parse_device_properties (struct mxt_data*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxt_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct mxt_data *data;
	int error;

	/*
	 * Ignore devices that do not have device properties attached to
	 * them, as we need help determining whether we are dealing with
	 * touch screen or touchpad.
	 *
	 * So far on x86 the only users of Atmel touch controllers are
	 * Chromebooks, and chromeos_laptop driver will ensure that
	 * necessary properties are provided (if firmware does not do that).
	 */
	if (!device_property_present(&client->dev, "compatible"))
		return -ENXIO;

	/*
	 * Ignore ACPI devices representing bootloader mode.
	 *
	 * This is a bit of a hack: Google Chromebook BIOS creates ACPI
	 * devices for both application and bootloader modes, but we are
	 * interested in application mode only (if device is in bootloader
	 * mode we'll end up switching into application anyway). So far
	 * application mode addresses were all above 0x40, so we'll use it
	 * as a threshold.
	 */
	if (ACPI_COMPANION(&client->dev) && client->addr < 0x40)
		return -ENXIO;

	data = devm_kzalloc(&client->dev, sizeof(struct mxt_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	snprintf(data->phys, sizeof(data->phys), "i2c-%u-%04x/input0",
		 client->adapter->nr, client->addr);

	data->client = client;
	data->irq = client->irq;
	i2c_set_clientdata(client, data);

	init_completion(&data->bl_completion);
	init_completion(&data->reset_completion);
	init_completion(&data->crc_completion);

	data->suspend_mode = dmi_check_system(chromebook_T9_suspend_dmi) ?
		MXT_SUSPEND_T9_CTRL : MXT_SUSPEND_DEEP_SLEEP;

	error = mxt_parse_device_properties(data);
	if (error)
		return error;

	data->reset_gpio = devm_gpiod_get_optional(&client->dev,
						   "reset", GPIOD_OUT_LOW);
	if (IS_ERR(data->reset_gpio)) {
		error = PTR_ERR(data->reset_gpio);
		dev_err(&client->dev, "Failed to get reset gpio: %d\n", error);
		return error;
	}

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, mxt_interrupt, IRQF_ONESHOT,
					  client->name, data);
	if (error) {
		dev_err(&client->dev, "Failed to register interrupt\n");
		return error;
	}

	disable_irq(client->irq);

	if (data->reset_gpio) {
		msleep(MXT_RESET_GPIO_TIME);
		gpiod_set_value(data->reset_gpio, 1);
		msleep(MXT_RESET_INVALID_CHG);
	}

	error = mxt_initialize(data);
	if (error)
		return error;

	error = sysfs_create_group(&client->dev.kobj, &mxt_attr_group);
	if (error) {
		dev_err(&client->dev, "Failure %d creating sysfs group\n",
			error);
		goto err_free_object;
	}

	return 0;

err_free_object:
	mxt_free_input_device(data);
	mxt_free_object_table(data);
	return error;
}