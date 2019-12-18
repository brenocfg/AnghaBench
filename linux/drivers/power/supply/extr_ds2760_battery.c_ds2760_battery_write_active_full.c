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
typedef  int /*<<< orphan*/  tmp ;
struct ds2760_device_info {unsigned char* raw; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t DS2760_ACTIVE_FULL ; 
 int /*<<< orphan*/  DS2760_EEPROM_BLOCK0 ; 
 int /*<<< orphan*/  w1_ds2760_recall_eeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_ds2760_store_eeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_ds2760_write (int /*<<< orphan*/ ,unsigned char*,size_t,int) ; 

__attribute__((used)) static void ds2760_battery_write_active_full(struct ds2760_device_info *di,
					     int active_full)
{
	unsigned char tmp[2] = {
		active_full >> 8,
		active_full & 0xff
	};

	if (tmp[0] == di->raw[DS2760_ACTIVE_FULL] &&
	    tmp[1] == di->raw[DS2760_ACTIVE_FULL + 1])
		return;

	w1_ds2760_write(di->dev, tmp, DS2760_ACTIVE_FULL, sizeof(tmp));
	w1_ds2760_store_eeprom(di->dev, DS2760_EEPROM_BLOCK0);
	w1_ds2760_recall_eeprom(di->dev, DS2760_EEPROM_BLOCK0);

	/* Write to the di->raw[] buffer directly - the DS2760_ACTIVE_FULL
	 * values won't be read back by ds2760_battery_read_status() */
	di->raw[DS2760_ACTIVE_FULL] = tmp[0];
	di->raw[DS2760_ACTIVE_FULL + 1] = tmp[1];
}