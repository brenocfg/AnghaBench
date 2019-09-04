#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lasat_eeprom_struct {int dummy; } ;
struct TYPE_3__ {unsigned long crc32; } ;
struct TYPE_4__ {TYPE_1__ li_eeprom_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROMWrite (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned long EEPROM_CRC (unsigned char*,int) ; 
 TYPE_2__ lasat_board_info ; 
 int /*<<< orphan*/  lasat_eeprom_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void lasat_write_eeprom_info(void)
{
	unsigned long crc;

	mutex_lock(&lasat_eeprom_mutex);

	/* Generate the CRC */
	crc = EEPROM_CRC((unsigned char *)(&lasat_board_info.li_eeprom_info),
		    sizeof(struct lasat_eeprom_struct) - 4);
	lasat_board_info.li_eeprom_info.crc32 = crc;

	/* Write the EEPROM info */
	EEPROMWrite(0, (unsigned char *)&lasat_board_info.li_eeprom_info,
		    sizeof(struct lasat_eeprom_struct));

	mutex_unlock(&lasat_eeprom_mutex);
}