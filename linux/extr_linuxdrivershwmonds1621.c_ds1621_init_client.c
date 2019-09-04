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
typedef  size_t u8 ;
struct i2c_client {int dummy; } ;
struct ds1621_data {int kind; int zbits; int /*<<< orphan*/  update_interval; } ;

/* Variables and functions */
 size_t DS1621_COM_START ; 
 int /*<<< orphan*/  DS1621_CONVERSION_MAX ; 
 int /*<<< orphan*/  DS1621_REG_CONF ; 
 size_t DS1621_REG_CONFIG_1SHOT ; 
 size_t DS1621_REG_CONFIG_POLARITY ; 
 size_t DS1621_REG_CONFIG_RESOL ; 
 size_t DS1621_REG_CONFIG_RESOL_SHIFT ; 
 int /*<<< orphan*/  DS1625_CONVERSION_MAX ; 
 size_t DS1721_COM_START ; 
#define  ds1625 131 
#define  ds1631 130 
#define  ds1721 129 
 int /*<<< orphan*/ * ds1721_convrates ; 
#define  ds1731 128 
 size_t i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte (struct i2c_client*,size_t) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,size_t) ; 
 int polarity ; 

__attribute__((used)) static void ds1621_init_client(struct ds1621_data *data,
			       struct i2c_client *client)
{
	u8 conf, new_conf, sreg, resol;

	new_conf = conf = i2c_smbus_read_byte_data(client, DS1621_REG_CONF);
	/* switch to continuous conversion mode */
	new_conf &= ~DS1621_REG_CONFIG_1SHOT;

	/* setup output polarity */
	if (polarity == 0)
		new_conf &= ~DS1621_REG_CONFIG_POLARITY;
	else if (polarity == 1)
		new_conf |= DS1621_REG_CONFIG_POLARITY;

	if (conf != new_conf)
		i2c_smbus_write_byte_data(client, DS1621_REG_CONF, new_conf);

	switch (data->kind) {
	case ds1625:
		data->update_interval = DS1625_CONVERSION_MAX;
		data->zbits = 7;
		sreg = DS1621_COM_START;
		break;
	case ds1631:
	case ds1721:
	case ds1731:
		resol = (new_conf & DS1621_REG_CONFIG_RESOL) >>
			 DS1621_REG_CONFIG_RESOL_SHIFT;
		data->update_interval = ds1721_convrates[resol];
		data->zbits = 7 - resol;
		sreg = DS1721_COM_START;
		break;
	default:
		data->update_interval = DS1621_CONVERSION_MAX;
		data->zbits = 7;
		sreg = DS1621_COM_START;
		break;
	}

	/* start conversion */
	i2c_smbus_write_byte(client, sreg);
}