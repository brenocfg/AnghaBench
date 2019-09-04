#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct i2c_adapter {int dummy; } ;
struct af9013_state {TYPE_1__* muxc; } ;
struct TYPE_2__ {struct i2c_adapter** adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct af9013_state* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static struct i2c_adapter *af9013_get_i2c_adapter(struct i2c_client *client)
{
	struct af9013_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	return state->muxc->adapter[0];
}