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
typedef  int u32 ;
typedef  int u16 ;
struct sht3x_limit_commands {int /*<<< orphan*/  write_command; } ;
struct sht3x_data {int* temperature_limits; int* humidity_limits; int /*<<< orphan*/  i2c_lock; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 size_t EIO ; 
 int SHT3X_CMD_LENGTH ; 
 int /*<<< orphan*/  SHT3X_CRC8_INIT ; 
 int SHT3X_CRC8_LEN ; 
 int SHT3X_WORD_LEN ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 char crc8 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct sht3x_data* dev_get_drvdata (struct device*) ; 
 int i2c_master_send (struct i2c_client*,char*,int) ; 
 struct sht3x_limit_commands* limit_commands ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sht3x_crc8_table ; 

__attribute__((used)) static size_t limit_store(struct device *dev,
			  size_t count,
			  u8 index,
			  int temperature,
			  u32 humidity)
{
	char buffer[SHT3X_CMD_LENGTH + SHT3X_WORD_LEN + SHT3X_CRC8_LEN];
	char *position = buffer;
	int ret;
	u16 raw;
	struct sht3x_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	const struct sht3x_limit_commands *commands;

	commands = &limit_commands[index];

	memcpy(position, commands->write_command, SHT3X_CMD_LENGTH);
	position += SHT3X_CMD_LENGTH;
	/*
	 * ST = (T + 45) / 175 * 2^16
	 * SRH = RH / 100 * 2^16
	 * adapted for fixed point arithmetic and packed the same as
	 * in limit_show()
	 */
	raw = ((u32)(temperature + 45000) * 24543) >> (16 + 7);
	raw |= ((humidity * 42950) >> 16) & 0xfe00;

	*((__be16 *)position) = cpu_to_be16(raw);
	position += SHT3X_WORD_LEN;
	*position = crc8(sht3x_crc8_table,
			 position - SHT3X_WORD_LEN,
			 SHT3X_WORD_LEN,
			 SHT3X_CRC8_INIT);

	mutex_lock(&data->i2c_lock);
	ret = i2c_master_send(client, buffer, sizeof(buffer));
	mutex_unlock(&data->i2c_lock);

	if (ret != sizeof(buffer))
		return ret < 0 ? ret : -EIO;

	data->temperature_limits[index] = temperature;
	data->humidity_limits[index] = humidity;
	return count;
}