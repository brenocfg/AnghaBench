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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_MAC_ADDRESS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/ * il_eeprom_query_addr (struct il_priv const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void
il4965_eeprom_get_mac(const struct il_priv *il, u8 * mac)
{
	const u8 *addr = il_eeprom_query_addr(il,
					      EEPROM_MAC_ADDRESS);
	memcpy(mac, addr, ETH_ALEN);
}