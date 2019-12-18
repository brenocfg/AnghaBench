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
struct adt7470_data {int /*<<< orphan*/  auto_update; } ;

/* Variables and functions */
 struct adt7470_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adt7470_remove(struct i2c_client *client)
{
	struct adt7470_data *data = i2c_get_clientdata(client);

	kthread_stop(data->auto_update);
	return 0;
}