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
struct smm665_data {int /*<<< orphan*/  conversion_time; struct i2c_client* cmdreg; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int SMM665_ADC_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smm665_read_adc(struct smm665_data *data, int adc)
{
	struct i2c_client *client = data->cmdreg;
	int rv;
	int radc;

	/*
	 * Algorithm for reading ADC, per SMM665 datasheet
	 *
	 *  {[S][addr][W][Ack]} {[offset][Ack]} {[S][addr][R][Nack]}
	 * [wait conversion time]
	 *  {[S][addr][R][Ack]} {[datahi][Ack]} {[datalo][Ack][P]}
	 *
	 * To implement the first part of this exchange,
	 * do a full read transaction and expect a failure/Nack.
	 * This sets up the address pointer on the SMM665
	 * and starts the ADC conversion.
	 * Then do a two-byte read transaction.
	 */
	rv = i2c_smbus_read_byte_data(client, adc << 3);
	if (rv != -ENXIO) {
		/*
		 * We expect ENXIO to reflect NACK
		 * (per Documentation/i2c/fault-codes.rst).
		 * Everything else is an error.
		 */
		dev_dbg(&client->dev,
			"Unexpected return code %d when setting ADC index", rv);
		return (rv < 0) ? rv : -EIO;
	}

	udelay(data->conversion_time);

	/*
	 * Now read two bytes.
	 *
	 * Neither i2c_smbus_read_byte() nor
	 * i2c_smbus_read_block_data() worked here,
	 * so use i2c_smbus_read_word_swapped() instead.
	 * We could also try to use i2c_master_recv(),
	 * but that is not always supported.
	 */
	rv = i2c_smbus_read_word_swapped(client, 0);
	if (rv < 0) {
		dev_dbg(&client->dev, "Failed to read ADC value: error %d", rv);
		return rv;
	}
	/*
	 * Validate/verify readback adc channel (in bit 11..14).
	 */
	radc = (rv >> 11) & 0x0f;
	if (radc != adc) {
		dev_dbg(&client->dev, "Unexpected RADC: Expected %d got %d",
			adc, radc);
		return -EIO;
	}

	return rv & SMM665_ADC_MASK;
}