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
struct isl29003_data {int* reg_cache; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ISL29003_ADC_PD ; 
 size_t ISL29003_REG_COMMAND ; 
 struct isl29003_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int isl29003_get_power_state(struct i2c_client *client)
{
	struct isl29003_data *data = i2c_get_clientdata(client);
	u8 cmdreg = data->reg_cache[ISL29003_REG_COMMAND];

	return ~cmdreg & ISL29003_ADC_PD;
}