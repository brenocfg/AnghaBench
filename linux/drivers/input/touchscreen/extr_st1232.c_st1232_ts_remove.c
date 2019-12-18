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
struct st1232_ts_data {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct st1232_ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  st1232_ts_power (struct st1232_ts_data*,int) ; 

__attribute__((used)) static int st1232_ts_remove(struct i2c_client *client)
{
	struct st1232_ts_data *ts = i2c_get_clientdata(client);

	st1232_ts_power(ts, false);

	return 0;
}