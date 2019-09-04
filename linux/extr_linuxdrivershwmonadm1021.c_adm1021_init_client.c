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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1021_REG_CONFIG_R ; 
 int /*<<< orphan*/  ADM1021_REG_CONFIG_W ; 
 int /*<<< orphan*/  ADM1021_REG_CONV_RATE_W ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adm1021_init_client(struct i2c_client *client)
{
	/* Enable ADC and disable suspend mode */
	i2c_smbus_write_byte_data(client, ADM1021_REG_CONFIG_W,
		i2c_smbus_read_byte_data(client, ADM1021_REG_CONFIG_R) & 0xBF);
	/* Set Conversion rate to 1/sec (this can be tinkered with) */
	i2c_smbus_write_byte_data(client, ADM1021_REG_CONV_RATE_W, 0x04);
}