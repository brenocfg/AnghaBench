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
struct bu21013_ts {int touch_stopped; } ;

/* Variables and functions */
 struct bu21013_ts* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int bu21013_remove(struct i2c_client *client)
{
	struct bu21013_ts *ts = i2c_get_clientdata(client);

	/* Make sure IRQ will exit quickly even if there is contact */
	ts->touch_stopped = true;
	/* The resources will be freed by devm */

	return 0;
}