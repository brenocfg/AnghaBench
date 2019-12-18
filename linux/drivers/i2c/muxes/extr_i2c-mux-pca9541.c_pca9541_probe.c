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
struct pca9541 {struct i2c_client* client; } ;
struct i2c_mux_core {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_LOCK_SEGMENT ; 
 int /*<<< orphan*/  I2C_MUX_ARBITRATOR ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_lock_bus (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_mux_add_adapter (struct i2c_mux_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_mux_core* i2c_mux_alloc (struct i2c_adapter*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pca9541* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct i2c_mux_core*) ; 
 int /*<<< orphan*/  i2c_unlock_bus (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pca9541_release_bus (struct i2c_client*) ; 
 int /*<<< orphan*/  pca9541_release_chan ; 
 int /*<<< orphan*/  pca9541_select_chan ; 

__attribute__((used)) static int pca9541_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct i2c_adapter *adap = client->adapter;
	struct i2c_mux_core *muxc;
	struct pca9541 *data;
	int ret;

	if (!i2c_check_functionality(adap, I2C_FUNC_SMBUS_BYTE_DATA))
		return -ENODEV;

	/*
	 * I2C accesses are unprotected here.
	 * We have to lock the I2C segment before releasing the bus.
	 */
	i2c_lock_bus(adap, I2C_LOCK_SEGMENT);
	pca9541_release_bus(client);
	i2c_unlock_bus(adap, I2C_LOCK_SEGMENT);

	/* Create mux adapter */

	muxc = i2c_mux_alloc(adap, &client->dev, 1, sizeof(*data),
			     I2C_MUX_ARBITRATOR,
			     pca9541_select_chan, pca9541_release_chan);
	if (!muxc)
		return -ENOMEM;

	data = i2c_mux_priv(muxc);
	data->client = client;

	i2c_set_clientdata(client, muxc);

	ret = i2c_mux_add_adapter(muxc, 0, 0, 0);
	if (ret)
		return ret;

	dev_info(&client->dev, "registered master selector for I2C %s\n",
		 client->name);

	return 0;
}