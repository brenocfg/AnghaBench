#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ipml200_dev {int /*<<< orphan*/ * rf; int /*<<< orphan*/  bd; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_PLATFORM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFKILL_TYPE_WLAN ; 
 int /*<<< orphan*/  backlight_device_register (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  cmpc_bl_ops ; 
 int /*<<< orphan*/  cmpc_rfkill_ops ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct ipml200_dev*) ; 
 int /*<<< orphan*/  kfree (struct ipml200_dev*) ; 
 struct ipml200_dev* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * rfkill_alloc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ *) ; 
 int rfkill_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmpc_ipml_add(struct acpi_device *acpi)
{
	int retval;
	struct ipml200_dev *ipml;
	struct backlight_properties props;

	ipml = kmalloc(sizeof(*ipml), GFP_KERNEL);
	if (ipml == NULL)
		return -ENOMEM;

	memset(&props, 0, sizeof(struct backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = 7;
	ipml->bd = backlight_device_register("cmpc_bl", &acpi->dev,
					     acpi->handle, &cmpc_bl_ops,
					     &props);
	if (IS_ERR(ipml->bd)) {
		retval = PTR_ERR(ipml->bd);
		goto out_bd;
	}

	ipml->rf = rfkill_alloc("cmpc_rfkill", &acpi->dev, RFKILL_TYPE_WLAN,
				&cmpc_rfkill_ops, acpi->handle);
	/*
	 * If RFKILL is disabled, rfkill_alloc will return ERR_PTR(-ENODEV).
	 * This is OK, however, since all other uses of the device will not
	 * derefence it.
	 */
	if (ipml->rf) {
		retval = rfkill_register(ipml->rf);
		if (retval) {
			rfkill_destroy(ipml->rf);
			ipml->rf = NULL;
		}
	}

	dev_set_drvdata(&acpi->dev, ipml);
	return 0;

out_bd:
	kfree(ipml);
	return retval;
}