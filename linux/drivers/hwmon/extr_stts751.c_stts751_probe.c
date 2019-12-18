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
struct stts751_priv {int notify_max; int notify_min; int config; int /*<<< orphan*/  dev; int /*<<< orphan*/  access_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int STTS751_CONF_EVENT_DIS ; 
 int STTS751_CONF_STOP ; 
 int /*<<< orphan*/  STTS751_REG_CONF ; 
 int /*<<< orphan*/  STTS751_REG_REV_ID ; 
 int /*<<< orphan*/  STTS751_REG_SMBUS_TO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_property_present (int /*<<< orphan*/ *,char*) ; 
 int device_property_read_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct stts751_priv*,int /*<<< orphan*/ ) ; 
 struct stts751_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct stts751_priv*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stts751_groups ; 
 int stts751_read_chip_config (struct stts751_priv*) ; 

__attribute__((used)) static int stts751_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct stts751_priv *priv;
	int ret;
	bool smbus_nto;
	int rev_id;

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->client = client;
	priv->notify_max = true;
	priv->notify_min = true;
	i2c_set_clientdata(client, priv);
	mutex_init(&priv->access_lock);

	if (device_property_present(&client->dev,
				    "smbus-timeout-disable")) {
		smbus_nto = device_property_read_bool(&client->dev,
						      "smbus-timeout-disable");

		ret = i2c_smbus_write_byte_data(client,	STTS751_REG_SMBUS_TO,
						smbus_nto ? 0 : 0x80);
		if (ret)
			return ret;
	}

	rev_id = i2c_smbus_read_byte_data(client, STTS751_REG_REV_ID);
	if (rev_id < 0)
		return -ENODEV;
	if (rev_id != 0x1) {
		dev_dbg(&client->dev, "Chip revision 0x%x is untested\n",
			rev_id);
	}

	ret = stts751_read_chip_config(priv);
	if (ret)
		return ret;

	priv->config &= ~(STTS751_CONF_STOP | STTS751_CONF_EVENT_DIS);
	ret = i2c_smbus_write_byte_data(client,	STTS751_REG_CONF, priv->config);
	if (ret)
		return ret;

	priv->dev = devm_hwmon_device_register_with_groups(&client->dev,
							client->name, priv,
							stts751_groups);
	return PTR_ERR_OR_ZERO(priv->dev);
}