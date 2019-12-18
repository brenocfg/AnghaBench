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
struct wmi_block {int /*<<< orphan*/  acpi_device; } ;

/* Variables and functions */
 char* acpi_device_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_guid (char const*,struct wmi_block**) ; 

char *wmi_get_acpi_device_uid(const char *guid_string)
{
	struct wmi_block *wblock = NULL;

	if (!find_guid(guid_string, &wblock))
		return NULL;

	return acpi_device_uid(wblock->acpi_device);
}