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
struct lm90_data {scalar_t__ kind; int /*<<< orphan*/  temp_hyst; int /*<<< orphan*/ * temp8; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM90_REG_W_TCRIT_HYST ; 
 size_t LOCAL_CRIT ; 
 scalar_t__ adt7461 ; 
 int /*<<< orphan*/  hyst_to_reg (int) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ max6646 ; 
 int temp_from_s8 (int /*<<< orphan*/ ) ; 
 int temp_from_u8 (int /*<<< orphan*/ ) ; 
 int temp_from_u8_adt7461 (struct lm90_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ tmp451 ; 

__attribute__((used)) static int lm90_set_temphyst(struct lm90_data *data, long val)
{
	struct i2c_client *client = data->client;
	int temp;
	int err;

	if (data->kind == adt7461 || data->kind == tmp451)
		temp = temp_from_u8_adt7461(data, data->temp8[LOCAL_CRIT]);
	else if (data->kind == max6646)
		temp = temp_from_u8(data->temp8[LOCAL_CRIT]);
	else
		temp = temp_from_s8(data->temp8[LOCAL_CRIT]);

	data->temp_hyst = hyst_to_reg(temp - val);
	err = i2c_smbus_write_byte_data(client, LM90_REG_W_TCRIT_HYST,
					data->temp_hyst);
	return err;
}