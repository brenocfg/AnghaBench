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
typedef  int /*<<< orphan*/  u8 ;
struct lm78_data {struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm78_write_value(struct lm78_data *data, u8 reg, u8 value)
{
	struct i2c_client *client = data->client;

#ifdef CONFIG_ISA
	if (!client) { /* ISA device */
		mutex_lock(&data->lock);
		outb_p(reg, data->isa_addr + LM78_ADDR_REG_OFFSET);
		outb_p(value, data->isa_addr + LM78_DATA_REG_OFFSET);
		mutex_unlock(&data->lock);
		return 0;
	} else
#endif
		return i2c_smbus_write_byte_data(client, reg, value);
}