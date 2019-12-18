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
typedef  int u8 ;
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeprom_cs (struct ipw_priv*) ; 
 int /*<<< orphan*/  eeprom_write_bit (struct ipw_priv*,int) ; 

__attribute__((used)) static void eeprom_op(struct ipw_priv *priv, u8 op, u8 addr)
{
	int i;

	eeprom_cs(priv);
	eeprom_write_bit(priv, 1);
	eeprom_write_bit(priv, op & 2);
	eeprom_write_bit(priv, op & 1);
	for (i = 7; i >= 0; i--) {
		eeprom_write_bit(priv, addr & (1 << i));
	}
}