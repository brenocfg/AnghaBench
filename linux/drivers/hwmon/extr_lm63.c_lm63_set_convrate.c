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
struct lm63_data {int max_convrate_hz; int /*<<< orphan*/  update_interval; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int LM63_MAX_CONVRATE ; 
 int /*<<< orphan*/  LM63_REG_CONVRATE ; 
 int /*<<< orphan*/  UPDATE_INTERVAL (int,int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lm63_set_convrate(struct lm63_data *data, unsigned int interval)
{
	struct i2c_client *client = data->client;
	unsigned int update_interval;
	int i;

	/* Shift calculations to avoid rounding errors */
	interval <<= 6;

	/* find the nearest update rate */
	update_interval = (1 << (LM63_MAX_CONVRATE + 6)) * 1000
	  / data->max_convrate_hz;
	for (i = 0; i < LM63_MAX_CONVRATE; i++, update_interval >>= 1)
		if (interval >= update_interval * 3 / 4)
			break;

	i2c_smbus_write_byte_data(client, LM63_REG_CONVRATE, i);
	data->update_interval = UPDATE_INTERVAL(data->max_convrate_hz, i);
}