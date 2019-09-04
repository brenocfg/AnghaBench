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
struct acpi_dev_match_info {char const* uid; int /*<<< orphan*/  hrv; TYPE_1__* hid; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_bus_type ; 
 int /*<<< orphan*/  acpi_dev_match_cb ; 
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct acpi_dev_match_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

bool acpi_dev_present(const char *hid, const char *uid, s64 hrv)
{
	struct acpi_dev_match_info match = {};
	struct device *dev;

	strlcpy(match.hid[0].id, hid, sizeof(match.hid[0].id));
	match.uid = uid;
	match.hrv = hrv;

	dev = bus_find_device(&acpi_bus_type, NULL, &match, acpi_dev_match_cb);
	put_device(dev);
	return !!dev;
}