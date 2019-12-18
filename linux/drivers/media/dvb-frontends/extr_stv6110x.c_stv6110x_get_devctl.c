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
struct stv6110x_state {struct stv6110x_devctl* devctl; } ;
struct stv6110x_devctl {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct stv6110x_state* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static struct stv6110x_devctl *stv6110x_get_devctl(struct i2c_client *client)
{
	struct stv6110x_state *stv6110x = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	return stv6110x->devctl;
}