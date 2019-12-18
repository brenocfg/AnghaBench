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
struct veml6070_data {int config; int /*<<< orphan*/  lock; int /*<<< orphan*/  client1; int /*<<< orphan*/  client2; } ;

/* Variables and functions */
 int VEML6070_COMMAND_SD ; 
 int i2c_smbus_read_byte (int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int veml6070_read(struct veml6070_data *data)
{
	int ret;
	u8 msb, lsb;

	mutex_lock(&data->lock);

	/* disable shutdown */
	ret = i2c_smbus_write_byte(data->client1,
	    data->config & ~VEML6070_COMMAND_SD);
	if (ret < 0)
		goto out;

	msleep(125 + 10); /* measurement takes up to 125 ms for IT 1x */

	ret = i2c_smbus_read_byte(data->client2); /* read MSB, address 0x39 */
	if (ret < 0)
		goto out;
	msb = ret;

	ret = i2c_smbus_read_byte(data->client1); /* read LSB, address 0x38 */
	if (ret < 0)
		goto out;
	lsb = ret;

	/* shutdown again */
	ret = i2c_smbus_write_byte(data->client1, data->config);
	if (ret < 0)
		goto out;

	ret = (msb << 8) | lsb;

out:
	mutex_unlock(&data->lock);
	return ret;
}