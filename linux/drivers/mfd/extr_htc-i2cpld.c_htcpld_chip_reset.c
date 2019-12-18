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
struct htcpld_chip {int /*<<< orphan*/  reset; int /*<<< orphan*/  cache_out; } ;

/* Variables and functions */
 struct htcpld_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void htcpld_chip_reset(struct i2c_client *client)
{
	struct htcpld_chip *chip_data = i2c_get_clientdata(client);
	if (!chip_data)
		return;

	i2c_smbus_read_byte_data(
		client, (chip_data->cache_out = chip_data->reset));
}