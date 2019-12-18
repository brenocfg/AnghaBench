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
struct sbsm_data {int /*<<< orphan*/  muxc; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct sbsm_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbsm_remove(struct i2c_client *client)
{
	struct sbsm_data *data = i2c_get_clientdata(client);

	i2c_mux_del_adapters(data->muxc);
	return 0;
}