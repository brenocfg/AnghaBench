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
struct acpi_sbs {int batteries_supported; int /*<<< orphan*/  hc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SBS_MANAGER ; 
 int /*<<< orphan*/  SMBUS_READ_WORD ; 
 int acpi_smbus_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_manager_get_info(struct acpi_sbs *sbs)
{
	int result = 0;
	u16 battery_system_info;

	result = acpi_smbus_read(sbs->hc, SMBUS_READ_WORD, ACPI_SBS_MANAGER,
				 0x04, (u8 *)&battery_system_info);
	if (!result)
		sbs->batteries_supported = battery_system_info & 0x000f;
	return result;
}