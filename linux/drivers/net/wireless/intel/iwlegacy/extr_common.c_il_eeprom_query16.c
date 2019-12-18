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
typedef  int u16 ;
struct il_priv {scalar_t__* eeprom; } ;

/* Variables and functions */

u16
il_eeprom_query16(const struct il_priv *il, size_t offset)
{
	if (!il->eeprom)
		return 0;
	return (u16) il->eeprom[offset] | ((u16) il->eeprom[offset + 1] << 8);
}