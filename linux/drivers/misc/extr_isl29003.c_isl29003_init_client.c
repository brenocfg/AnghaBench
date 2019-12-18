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
struct isl29003_data {int* reg_cache; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int ENODEV ; 
 struct isl29003_data* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  isl29003_set_mode (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isl29003_set_power_state (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isl29003_set_range (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isl29003_set_resolution (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isl29003_init_client(struct i2c_client *client)
{
	struct isl29003_data *data = i2c_get_clientdata(client);
	int i;

	/* read all the registers once to fill the cache.
	 * if one of the reads fails, we consider the init failed */
	for (i = 0; i < ARRAY_SIZE(data->reg_cache); i++) {
		int v = i2c_smbus_read_byte_data(client, i);

		if (v < 0)
			return -ENODEV;

		data->reg_cache[i] = v;
	}

	/* set defaults */
	isl29003_set_range(client, 0);
	isl29003_set_resolution(client, 0);
	isl29003_set_mode(client, 0);
	isl29003_set_power_state(client, 0);

	return 0;
}