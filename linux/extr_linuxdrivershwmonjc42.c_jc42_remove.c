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
struct jc42_data {int config; int orig_config; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int JC42_CFG_HYST_MASK ; 
 int /*<<< orphan*/  JC42_REG_CONFIG ; 
 struct jc42_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int jc42_remove(struct i2c_client *client)
{
	struct jc42_data *data = i2c_get_clientdata(client);

	/* Restore original configuration except hysteresis */
	if ((data->config & ~JC42_CFG_HYST_MASK) !=
	    (data->orig_config & ~JC42_CFG_HYST_MASK)) {
		int config;

		config = (data->orig_config & ~JC42_CFG_HYST_MASK)
		  | (data->config & JC42_CFG_HYST_MASK);
		i2c_smbus_write_word_swapped(client, JC42_REG_CONFIG, config);
	}
	return 0;
}