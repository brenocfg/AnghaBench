#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * release; } ;
struct TYPE_4__ {int /*<<< orphan*/ * demodulator_priv; TYPE_1__ ops; } ;
struct lgdt3306a_state {struct lgdt3306a_state* cfg; TYPE_2__ frontend; int /*<<< orphan*/  muxc; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct lgdt3306a_state* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lgdt3306a_state*) ; 

__attribute__((used)) static int lgdt3306a_remove(struct i2c_client *client)
{
	struct lgdt3306a_state *state = i2c_get_clientdata(client);

	i2c_mux_del_adapters(state->muxc);

	state->frontend.ops.release = NULL;
	state->frontend.demodulator_priv = NULL;

	kfree(state->cfg);
	kfree(state);

	return 0;
}