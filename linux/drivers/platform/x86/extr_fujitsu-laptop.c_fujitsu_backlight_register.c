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
struct fujitsu_bl {struct backlight_device* bl_device; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness_level; } ;
struct backlight_properties {int /*<<< orphan*/  type; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness; } ;
struct backlight_device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_PLATFORM ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct fujitsu_bl* acpi_driver_data (struct acpi_device*) ; 
 struct backlight_device* devm_backlight_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,struct acpi_device*,int /*<<< orphan*/ *,struct backlight_properties const*) ; 
 int /*<<< orphan*/  fujitsu_bl_ops ; 

__attribute__((used)) static int fujitsu_backlight_register(struct acpi_device *device)
{
	struct fujitsu_bl *priv = acpi_driver_data(device);
	const struct backlight_properties props = {
		.brightness = priv->brightness_level,
		.max_brightness = priv->max_brightness - 1,
		.type = BACKLIGHT_PLATFORM
	};
	struct backlight_device *bd;

	bd = devm_backlight_device_register(&device->dev, "fujitsu-laptop",
					    &device->dev, device,
					    &fujitsu_bl_ops, &props);
	if (IS_ERR(bd))
		return PTR_ERR(bd);

	priv->bl_device = bd;

	return 0;
}