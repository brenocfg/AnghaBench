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
struct i2c_client {int dummy; } ;
struct acpi_device_id {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline const struct acpi_device_id *
i2c_acpi_match_device(const struct acpi_device_id *matches,
		      struct i2c_client *client)
{
	return NULL;
}