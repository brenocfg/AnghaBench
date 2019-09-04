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
struct edt_ft5x06_ts_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  edt_ft5x06_ts_teardown_debugfs (struct edt_ft5x06_ts_data*) ; 
 struct edt_ft5x06_ts_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int edt_ft5x06_ts_remove(struct i2c_client *client)
{
	struct edt_ft5x06_ts_data *tsdata = i2c_get_clientdata(client);

	edt_ft5x06_ts_teardown_debugfs(tsdata);

	return 0;
}