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
struct lm90_data {scalar_t__ kind; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM90_REG_R_CONFIG1 ; 
 int /*<<< orphan*/  LM90_REG_W_CONFIG1 ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int lm90_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ max6696 ; 

__attribute__((used)) static inline int lm90_select_remote_channel(struct i2c_client *client,
					     struct lm90_data *data,
					     int channel)
{
	int config;

	if (data->kind == max6696) {
		config = lm90_read_reg(client, LM90_REG_R_CONFIG1);
		if (config < 0)
			return config;
		config &= ~0x08;
		if (channel)
			config |= 0x08;
		i2c_smbus_write_byte_data(client, LM90_REG_W_CONFIG1,
					  config);
	}
	return 0;
}