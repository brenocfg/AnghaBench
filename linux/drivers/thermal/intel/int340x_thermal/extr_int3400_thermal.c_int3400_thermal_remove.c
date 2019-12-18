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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_2__ dev; } ;
struct int3400_thermal_priv {struct int3400_thermal_priv* arts; struct int3400_thermal_priv* trts; int /*<<< orphan*/  thermal; TYPE_1__* adev; int /*<<< orphan*/  rel_misc_dev_res; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_thermal_rel_misc_device_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int3400_notify ; 
 int /*<<< orphan*/  kfree (struct int3400_thermal_priv*) ; 
 struct int3400_thermal_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_attribute_group ; 

__attribute__((used)) static int int3400_thermal_remove(struct platform_device *pdev)
{
	struct int3400_thermal_priv *priv = platform_get_drvdata(pdev);

	acpi_remove_notify_handler(
			priv->adev->handle, ACPI_DEVICE_NOTIFY,
			int3400_notify);

	if (!priv->rel_misc_dev_res)
		acpi_thermal_rel_misc_device_remove(priv->adev->handle);

	sysfs_remove_group(&pdev->dev.kobj, &uuid_attribute_group);
	thermal_zone_device_unregister(priv->thermal);
	kfree(priv->trts);
	kfree(priv->arts);
	kfree(priv);
	return 0;
}