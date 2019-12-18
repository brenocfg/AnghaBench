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
struct goodix_ts_data {int /*<<< orphan*/  firmware_loading_complete; scalar_t__ gpiod_rst; scalar_t__ gpiod_int; } ;

/* Variables and functions */
 struct goodix_ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int goodix_ts_remove(struct i2c_client *client)
{
	struct goodix_ts_data *ts = i2c_get_clientdata(client);

	if (ts->gpiod_int && ts->gpiod_rst)
		wait_for_completion(&ts->firmware_loading_complete);

	return 0;
}