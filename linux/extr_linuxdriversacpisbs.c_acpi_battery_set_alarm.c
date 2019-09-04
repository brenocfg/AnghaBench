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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct acpi_sbs {int /*<<< orphan*/  hc; scalar_t__ manager_present; } ;
struct acpi_battery {int id; int /*<<< orphan*/  alarm_capacity; struct acpi_sbs* sbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SBS_BATTERY ; 
 int /*<<< orphan*/  ACPI_SBS_MANAGER ; 
 int /*<<< orphan*/  SMBUS_READ_WORD ; 
 int /*<<< orphan*/  SMBUS_WRITE_WORD ; 
 int acpi_smbus_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int acpi_smbus_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int acpi_battery_set_alarm(struct acpi_battery *battery)
{
	struct acpi_sbs *sbs = battery->sbs;
	u16 value, sel = 1 << (battery->id + 12);

	int ret;


	if (sbs->manager_present) {
		ret = acpi_smbus_read(sbs->hc, SMBUS_READ_WORD, ACPI_SBS_MANAGER,
				0x01, (u8 *)&value);
		if (ret)
			goto end;
		if ((value & 0xf000) != sel) {
			value &= 0x0fff;
			value |= sel;
			ret = acpi_smbus_write(sbs->hc, SMBUS_WRITE_WORD,
					 ACPI_SBS_MANAGER,
					 0x01, (u8 *)&value, 2);
			if (ret)
				goto end;
		}
	}
	ret = acpi_smbus_write(sbs->hc, SMBUS_WRITE_WORD, ACPI_SBS_BATTERY,
				0x01, (u8 *)&battery->alarm_capacity, 2);
      end:
	return ret;
}