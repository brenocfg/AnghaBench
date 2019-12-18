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
struct mlxcpld_mux_plat_data {int num_adaps; int* adap_ids; } ;
struct mlxcpld_mux {scalar_t__ last_chan; struct i2c_client* client; } ;
struct i2c_mux_core {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int CPLD_MUX_MAX_NCHANS ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 struct mlxcpld_mux_plat_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_mux_add_adapter (struct i2c_mux_core*,int,int,int /*<<< orphan*/ ) ; 
 struct i2c_mux_core* i2c_mux_alloc (struct i2c_adapter*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (struct i2c_mux_core*) ; 
 struct mlxcpld_mux* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct i2c_mux_core*) ; 
 int /*<<< orphan*/  mlxcpld_mux_deselect ; 
 int /*<<< orphan*/  mlxcpld_mux_select_chan ; 

__attribute__((used)) static int mlxcpld_mux_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct i2c_adapter *adap = client->adapter;
	struct mlxcpld_mux_plat_data *pdata = dev_get_platdata(&client->dev);
	struct i2c_mux_core *muxc;
	int num, force;
	struct mlxcpld_mux *data;
	int err;

	if (!pdata)
		return -EINVAL;

	if (!i2c_check_functionality(adap, I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		return -ENODEV;

	muxc = i2c_mux_alloc(adap, &client->dev, CPLD_MUX_MAX_NCHANS,
			     sizeof(*data), 0, mlxcpld_mux_select_chan,
			     mlxcpld_mux_deselect);
	if (!muxc)
		return -ENOMEM;

	data = i2c_mux_priv(muxc);
	i2c_set_clientdata(client, muxc);
	data->client = client;
	data->last_chan = 0; /* force the first selection */

	/* Create an adapter for each channel. */
	for (num = 0; num < CPLD_MUX_MAX_NCHANS; num++) {
		if (num >= pdata->num_adaps)
			/* discard unconfigured channels */
			break;

		force = pdata->adap_ids[num];

		err = i2c_mux_add_adapter(muxc, force, num, 0);
		if (err)
			goto virt_reg_failed;
	}

	return 0;

virt_reg_failed:
	i2c_mux_del_adapters(muxc);
	return err;
}