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
struct mrfld_gpio {int /*<<< orphan*/  dev; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct acpi_device* acpi_dev_get_first_match_dev (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  acpi_dev_name (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_dev_put (struct acpi_device*) ; 
 char* devm_kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *mrfld_gpio_get_pinctrl_dev_name(struct mrfld_gpio *priv)
{
	struct acpi_device *adev;
	const char *name;

	adev = acpi_dev_get_first_match_dev("INTC1002", NULL, -1);
	if (adev) {
		name = devm_kstrdup(priv->dev, acpi_dev_name(adev), GFP_KERNEL);
		acpi_dev_put(adev);
	} else {
		name = "pinctrl-merrifield";
	}

	return name;
}