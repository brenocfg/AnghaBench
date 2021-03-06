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
struct i2c_client {int dummy; } ;
struct adm1275_data {scalar_t__ have_power_sampling; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1275_PMON_CONFIG ; 
 int ADM1275_VI_AVG_MASK ; 
 int ADM1275_VI_AVG_SHIFT ; 
 int ADM1278_PWR_AVG_MASK ; 
 int ADM1278_PWR_AVG_SHIFT ; 
 int ADM1278_VI_AVG_MASK ; 
 int ADM1278_VI_AVG_SHIFT ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adm1275_read_pmon_config(const struct adm1275_data *data,
				    struct i2c_client *client, bool is_power)
{
	int shift, ret;
	u16 mask;

	/*
	 * The PMON configuration register is a 16-bit register only on chips
	 * supporting power average sampling. On other chips it is an 8-bit
	 * register.
	 */
	if (data->have_power_sampling) {
		ret = i2c_smbus_read_word_data(client, ADM1275_PMON_CONFIG);
		mask = is_power ? ADM1278_PWR_AVG_MASK : ADM1278_VI_AVG_MASK;
		shift = is_power ? ADM1278_PWR_AVG_SHIFT : ADM1278_VI_AVG_SHIFT;
	} else {
		ret = i2c_smbus_read_byte_data(client, ADM1275_PMON_CONFIG);
		mask = ADM1275_VI_AVG_MASK;
		shift = ADM1275_VI_AVG_SHIFT;
	}
	if (ret < 0)
		return ret;

	return (ret & mask) >> shift;
}