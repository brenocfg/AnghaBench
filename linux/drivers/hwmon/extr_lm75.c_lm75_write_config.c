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
struct lm75_data {int current_conf; int /*<<< orphan*/  client; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LM75_REG_CONF ; 
 int LM75_SHUTDOWN ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lm75_write_config(struct lm75_data *data, u8 set_mask,
			     u8 clr_mask)
{
	u8 value;

	clr_mask |= LM75_SHUTDOWN;
	value = data->current_conf & ~clr_mask;
	value |= set_mask;

	if (data->current_conf != value) {
		s32 err;

		err = i2c_smbus_write_byte_data(data->client, LM75_REG_CONF,
						value);
		if (err)
			return err;
		data->current_conf = value;
	}
	return 0;
}