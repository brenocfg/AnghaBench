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
struct fujitsu_bl {int /*<<< orphan*/  max_brightness; } ;
struct acpi_device {struct fujitsu_bl* driver_data; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUJITSU_BL_DEVICE_NAME ; 
 int /*<<< orphan*/  ACPI_FUJITSU_CLASS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FUJITSU_LCD_N_LEVELS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ acpi_backlight_vendor ; 
 int /*<<< orphan*/  acpi_device_bid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int acpi_fujitsu_bl_input_setup (struct acpi_device*) ; 
 scalar_t__ acpi_video_get_backlight_type () ; 
 struct fujitsu_bl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int fujitsu_backlight_register (struct acpi_device*) ; 
 struct fujitsu_bl* fujitsu_bl ; 
 int /*<<< orphan*/  get_lcd_level (struct acpi_device*) ; 
 scalar_t__ get_max_brightness (struct acpi_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_fujitsu_bl_add(struct acpi_device *device)
{
	struct fujitsu_bl *priv;
	int ret;

	if (acpi_video_get_backlight_type() != acpi_backlight_vendor)
		return -ENODEV;

	priv = devm_kzalloc(&device->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	fujitsu_bl = priv;
	strcpy(acpi_device_name(device), ACPI_FUJITSU_BL_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_FUJITSU_CLASS);
	device->driver_data = priv;

	pr_info("ACPI: %s [%s]\n",
		acpi_device_name(device), acpi_device_bid(device));

	if (get_max_brightness(device) <= 0)
		priv->max_brightness = FUJITSU_LCD_N_LEVELS;
	get_lcd_level(device);

	ret = acpi_fujitsu_bl_input_setup(device);
	if (ret)
		return ret;

	return fujitsu_backlight_register(device);
}