#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct acpi_battery {TYPE_1__* sbs; } ;
struct TYPE_5__ {int offset; int /*<<< orphan*/  command; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  hc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SBS_BATTERY ; 
 int ARRAY_SIZE (TYPE_2__*) ; 
 int acpi_smbus_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* info_readers ; 

__attribute__((used)) static int acpi_battery_get_info(struct acpi_battery *battery)
{
	int i, result = 0;

	for (i = 0; i < ARRAY_SIZE(info_readers); ++i) {
		result = acpi_smbus_read(battery->sbs->hc,
					 info_readers[i].mode,
					 ACPI_SBS_BATTERY,
					 info_readers[i].command,
					 (u8 *) battery +
						info_readers[i].offset);
		if (result)
			break;
	}
	return result;
}