#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct acpi_sbs {scalar_t__ charger_present; int batteries_supported; struct acpi_battery* battery; scalar_t__ manager_present; TYPE_2__* charger; scalar_t__ charger_exists; } ;
struct acpi_battery {scalar_t__ present; TYPE_4__* bat; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int MAX_SBS_BAT ; 
 int /*<<< orphan*/  acpi_ac_get_present (struct acpi_sbs*) ; 
 int /*<<< orphan*/  acpi_battery_read (struct acpi_battery*) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_sbs_callback(void *context)
{
	int id;
	struct acpi_sbs *sbs = context;
	struct acpi_battery *bat;
	u8 saved_charger_state = sbs->charger_present;
	u8 saved_battery_state;

	if (sbs->charger_exists) {
		acpi_ac_get_present(sbs);
		if (sbs->charger_present != saved_charger_state)
			kobject_uevent(&sbs->charger->dev.kobj, KOBJ_CHANGE);
	}

	if (sbs->manager_present) {
		for (id = 0; id < MAX_SBS_BAT; ++id) {
			if (!(sbs->batteries_supported & (1 << id)))
				continue;
			bat = &sbs->battery[id];
			saved_battery_state = bat->present;
			acpi_battery_read(bat);
			if (saved_battery_state == bat->present)
				continue;
			kobject_uevent(&bat->bat->dev.kobj, KOBJ_CHANGE);
		}
	}
}