#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sbsm_data {int is_ltc1760; int supported_bats; TYPE_1__* muxc; int /*<<< orphan*/  psy; struct i2c_client* client; } ;
struct power_supply_desc {int name; } ;
struct power_supply_config {int /*<<< orphan*/  of_node; struct sbsm_data* drv_data; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int addr; struct device dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_4__ {struct sbsm_data* priv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPFNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  I2C_MUX_LOCKED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBSM_CMD_BATSYSINFO ; 
 int SBSM_MASK_BAT_SUPPORTED ; 
 int SBSM_MAX_BATS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct power_supply_desc* devm_kmemdup (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct sbsm_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (struct device*,struct power_supply_desc*,struct power_supply_config*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_mux_add_adapter (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* i2c_mux_alloc (struct i2c_adapter*,struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sbsm_data*) ; 
 int /*<<< orphan*/  sbsm_default_psy_desc ; 
 int sbsm_gpio_setup (struct sbsm_data*) ; 
 int sbsm_read_word (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbsm_select ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sbsm_probe(struct i2c_client *client,
		      const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct sbsm_data *data;
	struct device *dev = &client->dev;
	struct power_supply_desc *psy_desc;
	struct power_supply_config psy_cfg = {};
	int ret = 0, i;

	/* Device listens only at address 0x0a */
	if (client->addr != 0x0a)
		return -EINVAL;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA))
		return -EPFNOSUPPORT;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);

	data->client = client;
	data->is_ltc1760 = !!strstr(id->name, "ltc1760");

	ret  = sbsm_read_word(client, SBSM_CMD_BATSYSINFO);
	if (ret < 0)
		return ret;
	data->supported_bats = ret & SBSM_MASK_BAT_SUPPORTED;
	data->muxc = i2c_mux_alloc(adapter, dev, SBSM_MAX_BATS, 0,
				   I2C_MUX_LOCKED, &sbsm_select, NULL);
	if (!data->muxc) {
		dev_err(dev, "failed to alloc i2c mux\n");
		ret = -ENOMEM;
		goto err_mux_alloc;
	}
	data->muxc->priv = data;

	/* register muxed i2c channels. One for each supported battery */
	for (i = 0; i < SBSM_MAX_BATS; ++i) {
		if (data->supported_bats & BIT(i)) {
			ret = i2c_mux_add_adapter(data->muxc, 0, i + 1, 0);
			if (ret)
				break;
		}
	}
	if (ret) {
		dev_err(dev, "failed to register i2c mux channel %d\n", i + 1);
		goto err_mux_register;
	}

	psy_desc = devm_kmemdup(dev, &sbsm_default_psy_desc,
				sizeof(struct power_supply_desc),
				GFP_KERNEL);
	if (!psy_desc) {
		ret = -ENOMEM;
		goto err_psy;
	}

	psy_desc->name = devm_kasprintf(dev, GFP_KERNEL, "sbsm-%s",
					dev_name(&client->dev));
	if (!psy_desc->name) {
		ret = -ENOMEM;
		goto err_psy;
	}
	ret = sbsm_gpio_setup(data);
	if (ret < 0)
		goto err_psy;

	psy_cfg.drv_data = data;
	psy_cfg.of_node = dev->of_node;
	data->psy = devm_power_supply_register(dev, psy_desc, &psy_cfg);
	if (IS_ERR(data->psy)) {
		ret = PTR_ERR(data->psy);
		dev_err(dev, "failed to register power supply %s\n",
			psy_desc->name);
		goto err_psy;
	}

	return 0;

err_psy:
err_mux_register:
	i2c_mux_del_adapters(data->muxc);

err_mux_alloc:
	return ret;
}