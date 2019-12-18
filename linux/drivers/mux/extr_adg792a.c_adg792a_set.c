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
typedef  int /*<<< orphan*/  u8 ;
struct mux_control {TYPE_2__* chip; } ;
struct i2c_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int controllers; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADG792A_DISABLE (unsigned int) ; 
 int /*<<< orphan*/  ADG792A_DISABLE_ALL ; 
 int /*<<< orphan*/  ADG792A_MUX (unsigned int,int) ; 
 int /*<<< orphan*/  ADG792A_MUX_ALL (int) ; 
 int MUX_IDLE_DISCONNECT ; 
 int adg792a_write_cmd (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int mux_control_get_index (struct mux_control*) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adg792a_set(struct mux_control *mux, int state)
{
	struct i2c_client *i2c = to_i2c_client(mux->chip->dev.parent);
	u8 cmd;

	if (mux->chip->controllers == 1) {
		/* parallel mux controller operation */
		if (state == MUX_IDLE_DISCONNECT)
			cmd = ADG792A_DISABLE_ALL;
		else
			cmd = ADG792A_MUX_ALL(state);
	} else {
		unsigned int controller = mux_control_get_index(mux);

		if (state == MUX_IDLE_DISCONNECT)
			cmd = ADG792A_DISABLE(controller);
		else
			cmd = ADG792A_MUX(controller, state);
	}

	return adg792a_write_cmd(i2c, cmd, 0);
}