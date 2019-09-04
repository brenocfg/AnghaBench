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
struct af9013_state {int /*<<< orphan*/  regmap; int /*<<< orphan*/  muxc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct af9013_state* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct af9013_state*) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int af9013_remove(struct i2c_client *client)
{
	struct af9013_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	i2c_mux_del_adapters(state->muxc);

	regmap_exit(state->regmap);

	kfree(state);

	return 0;
}