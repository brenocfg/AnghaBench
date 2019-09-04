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
struct tc90522_state {int /*<<< orphan*/  tuner_i2c; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct tc90522_state* cfg_to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct tc90522_state*) ; 

__attribute__((used)) static int tc90522_remove(struct i2c_client *client)
{
	struct tc90522_state *state;

	state = cfg_to_state(i2c_get_clientdata(client));
	i2c_del_adapter(&state->tuner_i2c);
	kfree(state);
	return 0;
}