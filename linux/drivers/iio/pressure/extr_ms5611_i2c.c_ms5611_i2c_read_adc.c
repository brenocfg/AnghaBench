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
struct ms5611_state {int /*<<< orphan*/  client; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  MS5611_READ_ADC ; 
 int i2c_smbus_read_i2c_block_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int ms5611_i2c_read_adc(struct ms5611_state *st, s32 *val)
{
	int ret;
	u8 buf[3];

	ret = i2c_smbus_read_i2c_block_data(st->client, MS5611_READ_ADC,
					    3, buf);
	if (ret < 0)
		return ret;

	*val = (buf[0] << 16) | (buf[1] << 8) | buf[2];

	return 0;
}