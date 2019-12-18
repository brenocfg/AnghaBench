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
struct ds2760_device_info {unsigned char* raw; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2760_EEPROM_BLOCK1 ; 
 size_t DS2760_RATED_CAPACITY ; 
 int /*<<< orphan*/  w1_ds2760_recall_eeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_ds2760_store_eeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w1_ds2760_write (int /*<<< orphan*/ ,unsigned char*,size_t,int) ; 

__attribute__((used)) static void ds2760_battery_write_rated_capacity(struct ds2760_device_info *di,
						unsigned char rated_capacity)
{
	if (rated_capacity == di->raw[DS2760_RATED_CAPACITY])
		return;

	w1_ds2760_write(di->dev, &rated_capacity, DS2760_RATED_CAPACITY, 1);
	w1_ds2760_store_eeprom(di->dev, DS2760_EEPROM_BLOCK1);
	w1_ds2760_recall_eeprom(di->dev, DS2760_EEPROM_BLOCK1);
}