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
struct TYPE_4__ {TYPE_1__* fe; } ;
struct mxl301rf_state {TYPE_2__ cfg; } ;
struct i2c_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * tuner_priv; } ;

/* Variables and functions */
 struct mxl301rf_state* cfg_to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct mxl301rf_state*) ; 

__attribute__((used)) static int mxl301rf_remove(struct i2c_client *client)
{
	struct mxl301rf_state *state;

	state = cfg_to_state(i2c_get_clientdata(client));
	state->cfg.fe->tuner_priv = NULL;
	kfree(state);
	return 0;
}