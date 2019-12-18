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
struct fwnode_reference_args {int nargs; int /*<<< orphan*/ * args; int /*<<< orphan*/  fwnode; } ;
struct acpi_gpio_params {int /*<<< orphan*/  active_low; int /*<<< orphan*/  line_index; int /*<<< orphan*/  crs_entry_index; } ;
struct acpi_gpio_mapping {int size; unsigned int quirks; struct acpi_gpio_params* data; scalar_t__ name; } ;
struct acpi_device {struct acpi_gpio_mapping* driver_gpios; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_fwnode_handle (struct acpi_device*) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static bool acpi_get_driver_gpio_data(struct acpi_device *adev,
				      const char *name, int index,
				      struct fwnode_reference_args *args,
				      unsigned int *quirks)
{
	const struct acpi_gpio_mapping *gm;

	if (!adev->driver_gpios)
		return false;

	for (gm = adev->driver_gpios; gm->name; gm++)
		if (!strcmp(name, gm->name) && gm->data && index < gm->size) {
			const struct acpi_gpio_params *par = gm->data + index;

			args->fwnode = acpi_fwnode_handle(adev);
			args->args[0] = par->crs_entry_index;
			args->args[1] = par->line_index;
			args->args[2] = par->active_low;
			args->nargs = 3;

			*quirks = gm->quirks;
			return true;
		}

	return false;
}