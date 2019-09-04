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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {int dummy; } ;
struct af9013_state {struct dvb_frontend fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct af9013_state* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static struct dvb_frontend *af9013_get_dvb_frontend(struct i2c_client *client)
{
	struct af9013_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	return &state->fe;
}