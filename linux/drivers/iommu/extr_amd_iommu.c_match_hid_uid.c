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
struct device {int dummy; } ;
struct acpihid_map_entry {int /*<<< orphan*/ * uid; int /*<<< orphan*/ * hid; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int ENODEV ; 
 char* acpi_device_hid (struct acpi_device*) ; 
 char* acpi_device_uid (struct acpi_device*) ; 
 int strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int match_hid_uid(struct device *dev,
				struct acpihid_map_entry *entry)
{
	struct acpi_device *adev = ACPI_COMPANION(dev);
	const char *hid, *uid;

	if (!adev)
		return -ENODEV;

	hid = acpi_device_hid(adev);
	uid = acpi_device_uid(adev);

	if (!hid || !(*hid))
		return -ENODEV;

	if (!uid || !(*uid))
		return strcmp(hid, entry->hid);

	if (!(*entry->uid))
		return strcmp(hid, entry->hid);

	return (strcmp(hid, entry->hid) || strcmp(uid, entry->uid));
}