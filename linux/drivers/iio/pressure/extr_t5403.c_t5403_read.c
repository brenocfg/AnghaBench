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
struct t5403_data {int mode; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  T5403_COMMAND ; 
 int /*<<< orphan*/  T5403_DATA ; 
 int T5403_MODE_SHIFT ; 
 int T5403_PT ; 
 int T5403_SCO ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int* t5403_pressure_conv_ms ; 

__attribute__((used)) static int t5403_read(struct t5403_data *data, bool pressure)
{
	int wait_time = 3;  /* wakeup time in ms */

	int ret = i2c_smbus_write_byte_data(data->client, T5403_COMMAND,
		(pressure ? (data->mode << T5403_MODE_SHIFT) : T5403_PT) |
		T5403_SCO);
	if (ret < 0)
		return ret;

	wait_time += pressure ? t5403_pressure_conv_ms[data->mode] : 2;

	msleep(wait_time);

	return i2c_smbus_read_word_data(data->client, T5403_DATA);
}