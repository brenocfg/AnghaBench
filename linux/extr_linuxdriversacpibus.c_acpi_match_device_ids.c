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
struct acpi_device_id {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ __acpi_match_device (struct acpi_device*,struct acpi_device_id const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int acpi_match_device_ids(struct acpi_device *device,
			  const struct acpi_device_id *ids)
{
	return __acpi_match_device(device, ids, NULL, NULL, NULL) ? 0 : -ENOENT;
}