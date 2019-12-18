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
struct ipw_priv {int /*<<< orphan*/ * eeprom; } ;

/* Variables and functions */
 size_t EEPROM_VERSION ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_TRACE (char*) ; 
 scalar_t__ IPW_EEPROM_DATA ; 
 int IPW_EEPROM_IMAGE_SIZE ; 
 int /*<<< orphan*/  IPW_EEPROM_LOAD_DISABLE ; 
 int /*<<< orphan*/  ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipw_write8 (struct ipw_priv*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw_eeprom_init_sram(struct ipw_priv *priv)
{
	int i;

	IPW_DEBUG_TRACE(">>\n");

	/*
	   If the data looks correct, then copy it to our private
	   copy.  Otherwise let the firmware know to perform the operation
	   on its own.
	 */
	if (priv->eeprom[EEPROM_VERSION] != 0) {
		IPW_DEBUG_INFO("Writing EEPROM data into SRAM\n");

		/* write the eeprom data to sram */
		for (i = 0; i < IPW_EEPROM_IMAGE_SIZE; i++)
			ipw_write8(priv, IPW_EEPROM_DATA + i, priv->eeprom[i]);

		/* Do not load eeprom data on fatal error or suspend */
		ipw_write32(priv, IPW_EEPROM_LOAD_DISABLE, 0);
	} else {
		IPW_DEBUG_INFO("Enabling FW initialization of SRAM\n");

		/* Load eeprom data on fatal error or suspend */
		ipw_write32(priv, IPW_EEPROM_LOAD_DISABLE, 1);
	}

	IPW_DEBUG_TRACE("<<\n");
}