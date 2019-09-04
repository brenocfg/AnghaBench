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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ds620_platform_data {int pomode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS620_COM_START ; 
 int /*<<< orphan*/  DS620_REG_CONF ; 
 int DS620_REG_CONFIG_1SHOT ; 
 int DS620_REG_CONFIG_PO1 ; 
 int DS620_REG_CONFIG_PO2 ; 
 int DS620_REG_CONFIG_R0 ; 
 int DS620_REG_CONFIG_R1 ; 
 struct ds620_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ds620_init_client(struct i2c_client *client)
{
	struct ds620_platform_data *ds620_info = dev_get_platdata(&client->dev);
	u16 conf, new_conf;

	new_conf = conf =
	    i2c_smbus_read_word_swapped(client, DS620_REG_CONF);

	/* switch to continuous conversion mode */
	new_conf &= ~DS620_REG_CONFIG_1SHOT;
	/* already high at power-on, but don't trust the BIOS! */
	new_conf |= DS620_REG_CONFIG_PO2;
	/* thermostat mode according to platform data */
	if (ds620_info && ds620_info->pomode == 1)
		new_conf &= ~DS620_REG_CONFIG_PO1; /* PO_LOW */
	else if (ds620_info && ds620_info->pomode == 2)
		new_conf |= DS620_REG_CONFIG_PO1; /* PO_HIGH */
	else
		new_conf &= ~DS620_REG_CONFIG_PO2; /* always low */
	/* with highest precision */
	new_conf |= DS620_REG_CONFIG_R1 | DS620_REG_CONFIG_R0;

	if (conf != new_conf)
		i2c_smbus_write_word_swapped(client, DS620_REG_CONF, new_conf);

	/* start conversion */
	i2c_smbus_write_byte(client, DS620_COM_START);
}