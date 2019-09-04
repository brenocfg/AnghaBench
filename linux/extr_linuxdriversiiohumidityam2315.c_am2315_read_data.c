#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  tx_buf ;
struct am2315_sensor_data {int hum_data; int temp_data; } ;
struct am2315_data {int /*<<< orphan*/  lock; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  rx_buf ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AM2315_FUNCTION_READ ; 
 size_t AM2315_HUM_OFFSET ; 
 int AM2315_REG_HUM_MSB ; 
 size_t AM2315_TEMP_OFFSET ; 
 int EIO ; 
 int am2315_crc (int*,int) ; 
 int /*<<< orphan*/  am2315_ping (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_recv (TYPE_1__*,int*,int) ; 
 int i2c_master_send (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int am2315_read_data(struct am2315_data *data,
			    struct am2315_sensor_data *sensor_data)
{
	int ret;
	/* tx_buf format: <function code> <start addr> <nr of regs to read> */
	u8 tx_buf[3] = { AM2315_FUNCTION_READ, AM2315_REG_HUM_MSB, 4 };
	/*
	 * rx_buf format:
	 * <function code> <number of registers read>
	 * <humidity MSB> <humidity LSB> <temp MSB> <temp LSB>
	 * <CRC LSB> <CRC MSB>
	 */
	u8 rx_buf[8];
	u16 crc;

	/* First wake up the device. */
	am2315_ping(data->client);

	mutex_lock(&data->lock);
	ret = i2c_master_send(data->client, tx_buf, sizeof(tx_buf));
	if (ret < 0) {
		dev_err(&data->client->dev, "failed to send read request\n");
		goto exit_unlock;
	}
	/* Wait 2-3 ms, then read back the data sent by the device. */
	usleep_range(2000, 3000);
	/* Do a bulk data read, then pick out what we need. */
	ret = i2c_master_recv(data->client, rx_buf, sizeof(rx_buf));
	if (ret < 0) {
		dev_err(&data->client->dev, "failed to read sensor data\n");
		goto exit_unlock;
	}
	mutex_unlock(&data->lock);
	/*
	 * Do a CRC check on the data and compare it to the value
	 * calculated by the device.
	 */
	crc = am2315_crc(rx_buf, sizeof(rx_buf) - 2);
	if ((crc & 0xff) != rx_buf[6] || (crc >> 8) != rx_buf[7]) {
		dev_err(&data->client->dev, "failed to verify sensor data\n");
		return -EIO;
	}

	sensor_data->hum_data = (rx_buf[AM2315_HUM_OFFSET] << 8) |
				 rx_buf[AM2315_HUM_OFFSET + 1];
	sensor_data->temp_data = (rx_buf[AM2315_TEMP_OFFSET] << 8) |
				  rx_buf[AM2315_TEMP_OFFSET + 1];

	return ret;

exit_unlock:
	mutex_unlock(&data->lock);
	return ret;
}