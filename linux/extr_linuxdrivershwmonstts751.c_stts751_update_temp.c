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
struct stts751_priv {int /*<<< orphan*/  temp; TYPE_1__* client; } ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STTS751_REG_TEMP_H ; 
 int /*<<< orphan*/  STTS751_REG_TEMP_L ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stts751_to_deg (int) ; 

__attribute__((used)) static int stts751_update_temp(struct stts751_priv *priv)
{
	s32 integer1, integer2, frac;

	/*
	 * There is a trick here, like in the lm90 driver. We have to read two
	 * registers to get the sensor temperature, but we have to beware a
	 * conversion could occur between the readings. We could use the
	 * one-shot conversion register, but we don't want to do this (disables
	 * hardware monitoring). So the solution used here is to read the high
	 * byte once, then the low byte, then the high byte again. If the new
	 * high byte matches the old one, then we have a valid reading. Else we
	 * have to read the low byte again, and now we believe we have a correct
	 * reading.
	 */
	integer1 = i2c_smbus_read_byte_data(priv->client, STTS751_REG_TEMP_H);
	if (integer1 < 0) {
		dev_dbg(&priv->client->dev,
			"I2C read failed (temp H). ret: %x\n", integer1);
		return integer1;
	}

	frac = i2c_smbus_read_byte_data(priv->client, STTS751_REG_TEMP_L);
	if (frac < 0) {
		dev_dbg(&priv->client->dev,
			"I2C read failed (temp L). ret: %x\n", frac);
		return frac;
	}

	integer2 = i2c_smbus_read_byte_data(priv->client, STTS751_REG_TEMP_H);
	if (integer2 < 0) {
		dev_dbg(&priv->client->dev,
			"I2C 2nd read failed (temp H). ret: %x\n", integer2);
		return integer2;
	}

	if (integer1 != integer2) {
		frac = i2c_smbus_read_byte_data(priv->client,
						STTS751_REG_TEMP_L);
		if (frac < 0) {
			dev_dbg(&priv->client->dev,
				"I2C 2nd read failed (temp L). ret: %x\n",
				frac);
			return frac;
		}
	}

	priv->temp = stts751_to_deg((integer1 << 8) | frac);
	return 0;
}