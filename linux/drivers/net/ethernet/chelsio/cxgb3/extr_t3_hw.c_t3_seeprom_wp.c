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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_STAT_ADDR ; 
 int t3_seeprom_write (struct adapter*,int /*<<< orphan*/ ,int) ; 

int t3_seeprom_wp(struct adapter *adapter, int enable)
{
	return t3_seeprom_write(adapter, EEPROM_STAT_ADDR, enable ? 0xc : 0);
}