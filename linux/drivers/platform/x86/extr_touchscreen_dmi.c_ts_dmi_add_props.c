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
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  properties; int /*<<< orphan*/  acpi_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int device_add_properties (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ has_acpi_companion (struct device*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ts_data ; 

__attribute__((used)) static void ts_dmi_add_props(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	int error;

	if (has_acpi_companion(dev) &&
	    !strncmp(ts_data->acpi_name, client->name, I2C_NAME_SIZE)) {
		error = device_add_properties(dev, ts_data->properties);
		if (error)
			dev_err(dev, "failed to add properties: %d\n", error);
	}
}