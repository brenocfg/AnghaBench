#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct il_priv {int /*<<< orphan*/  const* eeprom; TYPE_1__* cfg; } ;
struct TYPE_2__ {size_t eeprom_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

const u8 *
il_eeprom_query_addr(const struct il_priv *il, size_t offset)
{
	BUG_ON(offset >= il->cfg->eeprom_size);
	return &il->eeprom[offset];
}