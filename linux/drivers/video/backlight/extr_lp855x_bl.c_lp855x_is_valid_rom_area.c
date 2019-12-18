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
typedef  scalar_t__ u8 ;
struct lp855x {int chip_id; } ;

/* Variables and functions */
#define  LP8550 134 
#define  LP8551 133 
#define  LP8552 132 
#define  LP8553 131 
#define  LP8555 130 
 scalar_t__ LP8555_EPROM_END ; 
 scalar_t__ LP8555_EPROM_START ; 
#define  LP8556 129 
 scalar_t__ LP8556_EPROM_END ; 
 scalar_t__ LP8556_EPROM_START ; 
#define  LP8557 128 
 scalar_t__ LP8557_EPROM_END ; 
 scalar_t__ LP8557_EPROM_START ; 
 scalar_t__ LP855X_EEPROM_END ; 
 scalar_t__ LP855X_EEPROM_START ; 

__attribute__((used)) static bool lp855x_is_valid_rom_area(struct lp855x *lp, u8 addr)
{
	u8 start, end;

	switch (lp->chip_id) {
	case LP8550:
	case LP8551:
	case LP8552:
	case LP8553:
		start = LP855X_EEPROM_START;
		end = LP855X_EEPROM_END;
		break;
	case LP8556:
		start = LP8556_EPROM_START;
		end = LP8556_EPROM_END;
		break;
	case LP8555:
		start = LP8555_EPROM_START;
		end = LP8555_EPROM_END;
		break;
	case LP8557:
		start = LP8557_EPROM_START;
		end = LP8557_EPROM_END;
		break;
	default:
		return false;
	}

	return addr >= start && addr <= end;
}