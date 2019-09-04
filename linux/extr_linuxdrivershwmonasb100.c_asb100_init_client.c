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
struct asb100_data {int /*<<< orphan*/  vrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASB100_REG_CONFIG ; 
 int asb100_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asb100_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct asb100_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static void asb100_init_client(struct i2c_client *client)
{
	struct asb100_data *data = i2c_get_clientdata(client);

	data->vrm = vid_which_vrm();

	/* Start monitoring */
	asb100_write_value(client, ASB100_REG_CONFIG,
		(asb100_read_value(client, ASB100_REG_CONFIG) & 0xf7) | 0x01);
}