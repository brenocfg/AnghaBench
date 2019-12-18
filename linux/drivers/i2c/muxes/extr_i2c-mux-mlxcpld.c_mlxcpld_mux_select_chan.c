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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct mlxcpld_mux {scalar_t__ last_chan; struct i2c_client* client; } ;
struct i2c_mux_core {int /*<<< orphan*/  parent; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct mlxcpld_mux* i2c_mux_priv (struct i2c_mux_core*) ; 
 int mlxcpld_mux_reg_write (int /*<<< orphan*/ ,struct i2c_client*,scalar_t__) ; 

__attribute__((used)) static int mlxcpld_mux_select_chan(struct i2c_mux_core *muxc, u32 chan)
{
	struct mlxcpld_mux *data = i2c_mux_priv(muxc);
	struct i2c_client *client = data->client;
	u8 regval = chan + 1;
	int err = 0;

	/* Only select the channel if its different from the last channel */
	if (data->last_chan != regval) {
		err = mlxcpld_mux_reg_write(muxc->parent, client, regval);
		data->last_chan = err < 0 ? 0 : regval;
	}

	return err;
}