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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int EEPROM_BIT_CS ; 
 int EEPROM_BIT_SK ; 
 int /*<<< orphan*/  eeprom_write_reg (struct ipw_priv*,int) ; 

__attribute__((used)) static void eeprom_cs(struct ipw_priv *priv)
{
	eeprom_write_reg(priv, 0);
	eeprom_write_reg(priv, EEPROM_BIT_CS);
	eeprom_write_reg(priv, EEPROM_BIT_CS | EEPROM_BIT_SK);
	eeprom_write_reg(priv, EEPROM_BIT_CS);
}