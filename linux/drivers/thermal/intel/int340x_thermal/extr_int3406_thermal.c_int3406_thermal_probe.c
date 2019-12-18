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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct int3406_thermal_data {int /*<<< orphan*/  br; int /*<<< orphan*/  cooling_dev; struct backlight_device* raw_bd; scalar_t__ handle; } ;
struct backlight_device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_device_bid (struct acpi_device*) ; 
 int acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct int3406_thermal_data*) ; 
 int acpi_video_get_levels (struct acpi_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct backlight_device* backlight_device_get_by_type (int /*<<< orphan*/ ) ; 
 struct int3406_thermal_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int3406_notify ; 
 int /*<<< orphan*/  int3406_thermal_get_limit (struct int3406_thermal_data*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct int3406_thermal_data*) ; 
 int /*<<< orphan*/  thermal_cooling_device_register (int /*<<< orphan*/ ,struct int3406_thermal_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_cooling_ops ; 

__attribute__((used)) static int int3406_thermal_probe(struct platform_device *pdev)
{
	struct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	struct int3406_thermal_data *d;
	struct backlight_device *bd;
	int ret;

	if (!ACPI_HANDLE(&pdev->dev))
		return -ENODEV;

	d = devm_kzalloc(&pdev->dev, sizeof(*d), GFP_KERNEL);
	if (!d)
		return -ENOMEM;
	d->handle = ACPI_HANDLE(&pdev->dev);

	bd = backlight_device_get_by_type(BACKLIGHT_RAW);
	if (!bd)
		return -ENODEV;
	d->raw_bd = bd;

	ret = acpi_video_get_levels(ACPI_COMPANION(&pdev->dev), &d->br, NULL);
	if (ret)
		return ret;

	int3406_thermal_get_limit(d);

	d->cooling_dev = thermal_cooling_device_register(acpi_device_bid(adev),
							 d, &video_cooling_ops);
	if (IS_ERR(d->cooling_dev))
		goto err;

	ret = acpi_install_notify_handler(adev->handle, ACPI_DEVICE_NOTIFY,
					  int3406_notify, d);
	if (ret)
		goto err_cdev;

	platform_set_drvdata(pdev, d);

	return 0;

err_cdev:
	thermal_cooling_device_unregister(d->cooling_dev);
err:
	kfree(d->br);
	return -ENODEV;
}