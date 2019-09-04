#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  long u32 ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {TYPE_3__* adapter; struct device dev; } ;
struct atmel_ecc_i2c_client_priv {int /*<<< orphan*/  i2c_client_list_node; int /*<<< orphan*/  tfm_count; int /*<<< orphan*/  wake_token; int /*<<< orphan*/  wake_token_sz; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_8__ {long cra_driver_name; } ;
struct TYPE_11__ {TYPE_2__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/  i2c_list_lock; int /*<<< orphan*/  i2c_client_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  atmel_ecc_wake_token_sz (long) ; 
 TYPE_5__ atmel_ecdh ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypto_register_kpp (TYPE_5__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int device_sanity_check (struct i2c_client*) ; 
 struct atmel_ecc_i2c_client_priv* devm_kmalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__ driver_data ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct atmel_ecc_i2c_client_priv*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,long*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_ecc_probe(struct i2c_client *client,
			   const struct i2c_device_id *id)
{
	struct atmel_ecc_i2c_client_priv *i2c_priv;
	struct device *dev = &client->dev;
	int ret;
	u32 bus_clk_rate;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(dev, "I2C_FUNC_I2C not supported\n");
		return -ENODEV;
	}

	ret = of_property_read_u32(client->adapter->dev.of_node,
				   "clock-frequency", &bus_clk_rate);
	if (ret) {
		dev_err(dev, "of: failed to read clock-frequency property\n");
		return ret;
	}

	if (bus_clk_rate > 1000000L) {
		dev_err(dev, "%d exceeds maximum supported clock frequency (1MHz)\n",
			bus_clk_rate);
		return -EINVAL;
	}

	i2c_priv = devm_kmalloc(dev, sizeof(*i2c_priv), GFP_KERNEL);
	if (!i2c_priv)
		return -ENOMEM;

	i2c_priv->client = client;
	mutex_init(&i2c_priv->lock);

	/*
	 * WAKE_TOKEN_MAX_SIZE was calculated for the maximum bus_clk_rate -
	 * 1MHz. The previous bus_clk_rate check ensures us that wake_token_sz
	 * will always be smaller than or equal to WAKE_TOKEN_MAX_SIZE.
	 */
	i2c_priv->wake_token_sz = atmel_ecc_wake_token_sz(bus_clk_rate);

	memset(i2c_priv->wake_token, 0, sizeof(i2c_priv->wake_token));

	atomic_set(&i2c_priv->tfm_count, 0);

	i2c_set_clientdata(client, i2c_priv);

	ret = device_sanity_check(client);
	if (ret)
		return ret;

	spin_lock(&driver_data.i2c_list_lock);
	list_add_tail(&i2c_priv->i2c_client_list_node,
		      &driver_data.i2c_client_list);
	spin_unlock(&driver_data.i2c_list_lock);

	ret = crypto_register_kpp(&atmel_ecdh);
	if (ret) {
		spin_lock(&driver_data.i2c_list_lock);
		list_del(&i2c_priv->i2c_client_list_node);
		spin_unlock(&driver_data.i2c_list_lock);

		dev_err(dev, "%s alg registration failed\n",
			atmel_ecdh.base.cra_driver_name);
	} else {
		dev_info(dev, "atmel ecc algorithms registered in /proc/crypto\n");
	}

	return ret;
}