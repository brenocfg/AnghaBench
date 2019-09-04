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
struct acpi_sbs {int charger_present; int /*<<< orphan*/  hc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SBS_CHARGER ; 
 int ENODEV ; 
 int /*<<< orphan*/  SMBUS_READ_WORD ; 
 int acpi_smbus_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_ac_get_present(struct acpi_sbs *sbs)
{
	int result;
	u16 status;

	result = acpi_smbus_read(sbs->hc, SMBUS_READ_WORD, ACPI_SBS_CHARGER,
				 0x13, (u8 *) & status);

	if (result)
		return result;

	/*
	 * The spec requires that bit 4 always be 1. If it's not set, assume
	 * that the implementation doesn't support an SBS charger.
	 *
	 * And on some MacBooks a status of 0xffff is always returned, no
	 * matter whether the charger is plugged in or not, which is also
	 * wrong, so ignore the SBS charger for those too.
	 */
	if (!((status >> 4) & 0x1) || status == 0xffff)
		return -ENODEV;

	sbs->charger_present = (status >> 15) & 0x1;
	return 0;
}