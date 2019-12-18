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
struct mcs_touchkey_data {int /*<<< orphan*/  (* poweron ) (int) ;} ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct mcs_touchkey_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void mcs_touchkey_shutdown(struct i2c_client *client)
{
	struct mcs_touchkey_data *data = i2c_get_clientdata(client);

	if (data->poweron)
		data->poweron(false);
}