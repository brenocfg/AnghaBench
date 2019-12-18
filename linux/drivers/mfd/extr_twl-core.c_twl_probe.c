#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct twl_private {int dummy; } ;
struct twl_client {struct i2c_client* regmap; struct i2c_client* client; } ;
struct twl4030_platform_data {int /*<<< orphan*/  gpio; int /*<<< orphan*/ * clock; } ;
struct regmap_config {int dummy; } ;
struct platform_device {int dummy; } ;
struct i2c_device_id {int driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_19__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_4__ dev; scalar_t__ irq; scalar_t__ addr; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  base; } ;
struct TYPE_17__ {int /*<<< orphan*/  platform_data; } ;
struct TYPE_16__ {int ready; struct twl_client* twl_modules; TYPE_3__* twl_map; int /*<<< orphan*/  twl_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int I2C_SCL_CTRL_PU ; 
 int I2C_SDA_CTRL_PU ; 
 scalar_t__ IS_ERR (struct i2c_client*) ; 
 int PTR_ERR (struct i2c_client*) ; 
 int /*<<< orphan*/  REG_GPPUPDCTR1 ; 
 int SMARTREFLEX_ENABLE ; 
 int SR_I2C_SCL_CTRL_PU ; 
 int SR_I2C_SDA_CTRL_PU ; 
 int /*<<< orphan*/  TWL4030_CLASS_ID ; 
 int /*<<< orphan*/  TWL4030_DCDC_GLOBAL_CFG ; 
 int /*<<< orphan*/  TWL4030_MODULE_INTBR ; 
 int TWL6030_CLASS ; 
 int /*<<< orphan*/  TWL6030_CLASS_ID ; 
 int /*<<< orphan*/  TWL6032_BASEADD_CHARGER ; 
 int TWL6032_SUBCLASS ; 
 size_t TWL_MODULE_MAIN_CHARGE ; 
 int /*<<< orphan*/  TWL_MODULE_PM_RECEIVER ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int add_children (struct twl4030_platform_data*,int,int) ; 
 int /*<<< orphan*/  clocks_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 struct twl4030_platform_data* dev_get_platdata (TYPE_4__*) ; 
 struct twl_client* devm_kcalloc (TYPE_4__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 struct i2c_client* devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 scalar_t__ i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* i2c_new_dummy_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,TYPE_2__*,TYPE_4__*) ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  twl4030_init_chip_irq (int /*<<< orphan*/ ) ; 
 int twl4030_init_irq (TYPE_4__*,scalar_t__) ; 
 TYPE_3__* twl4030_map ; 
 struct regmap_config* twl4030_regmap_config ; 
 int twl6030_init_irq (TYPE_4__*,scalar_t__) ; 
 TYPE_3__* twl6030_map ; 
 struct regmap_config* twl6030_regmap_config ; 
 TYPE_2__* twl_auxdata_lookup ; 
 scalar_t__ twl_class_is_4030 () ; 
 unsigned int twl_get_num_slaves () ; 
 int /*<<< orphan*/  twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* twl_priv ; 
 int twl_read_idcode_register () ; 
 int /*<<< orphan*/  twl_remove (struct i2c_client*) ; 

__attribute__((used)) static int
twl_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct twl4030_platform_data	*pdata = dev_get_platdata(&client->dev);
	struct device_node		*node = client->dev.of_node;
	struct platform_device		*pdev;
	const struct regmap_config	*twl_regmap_config;
	int				irq_base = 0;
	int				status;
	unsigned			i, num_slaves;

	if (!node && !pdata) {
		dev_err(&client->dev, "no platform data\n");
		return -EINVAL;
	}

	if (twl_priv) {
		dev_dbg(&client->dev, "only one instance of %s allowed\n",
			DRIVER_NAME);
		return -EBUSY;
	}

	pdev = platform_device_alloc(DRIVER_NAME, -1);
	if (!pdev) {
		dev_err(&client->dev, "can't alloc pdev\n");
		return -ENOMEM;
	}

	status = platform_device_add(pdev);
	if (status) {
		platform_device_put(pdev);
		return status;
	}

	if (i2c_check_functionality(client->adapter, I2C_FUNC_I2C) == 0) {
		dev_dbg(&client->dev, "can't talk I2C?\n");
		status = -EIO;
		goto free;
	}

	twl_priv = devm_kzalloc(&client->dev, sizeof(struct twl_private),
				GFP_KERNEL);
	if (!twl_priv) {
		status = -ENOMEM;
		goto free;
	}

	if ((id->driver_data) & TWL6030_CLASS) {
		twl_priv->twl_id = TWL6030_CLASS_ID;
		twl_priv->twl_map = &twl6030_map[0];
		/* The charger base address is different in twl6032 */
		if ((id->driver_data) & TWL6032_SUBCLASS)
			twl_priv->twl_map[TWL_MODULE_MAIN_CHARGE].base =
							TWL6032_BASEADD_CHARGER;
		twl_regmap_config = twl6030_regmap_config;
	} else {
		twl_priv->twl_id = TWL4030_CLASS_ID;
		twl_priv->twl_map = &twl4030_map[0];
		twl_regmap_config = twl4030_regmap_config;
	}

	num_slaves = twl_get_num_slaves();
	twl_priv->twl_modules = devm_kcalloc(&client->dev,
					 num_slaves,
					 sizeof(struct twl_client),
					 GFP_KERNEL);
	if (!twl_priv->twl_modules) {
		status = -ENOMEM;
		goto free;
	}

	for (i = 0; i < num_slaves; i++) {
		struct twl_client *twl = &twl_priv->twl_modules[i];

		if (i == 0) {
			twl->client = client;
		} else {
			twl->client = i2c_new_dummy_device(client->adapter,
						    client->addr + i);
			if (IS_ERR(twl->client)) {
				dev_err(&client->dev,
					"can't attach client %d\n", i);
				status = PTR_ERR(twl->client);
				goto fail;
			}
		}

		twl->regmap = devm_regmap_init_i2c(twl->client,
						   &twl_regmap_config[i]);
		if (IS_ERR(twl->regmap)) {
			status = PTR_ERR(twl->regmap);
			dev_err(&client->dev,
				"Failed to allocate regmap %d, err: %d\n", i,
				status);
			goto fail;
		}
	}

	twl_priv->ready = true;

	/* setup clock framework */
	clocks_init(&client->dev, pdata ? pdata->clock : NULL);

	/* read TWL IDCODE Register */
	if (twl_class_is_4030()) {
		status = twl_read_idcode_register();
		WARN(status < 0, "Error: reading twl_idcode register value\n");
	}

	/* Maybe init the T2 Interrupt subsystem */
	if (client->irq) {
		if (twl_class_is_4030()) {
			twl4030_init_chip_irq(id->name);
			irq_base = twl4030_init_irq(&client->dev, client->irq);
		} else {
			irq_base = twl6030_init_irq(&client->dev, client->irq);
		}

		if (irq_base < 0) {
			status = irq_base;
			goto fail;
		}
	}

	/*
	 * Disable TWL4030/TWL5030 I2C Pull-up on I2C1 and I2C4(SR) interface.
	 * Program I2C_SCL_CTRL_PU(bit 0)=0, I2C_SDA_CTRL_PU (bit 2)=0,
	 * SR_I2C_SCL_CTRL_PU(bit 4)=0 and SR_I2C_SDA_CTRL_PU(bit 6)=0.
	 *
	 * Also, always enable SmartReflex bit as that's needed for omaps to
	 * to do anything over I2C4 for voltage scaling even if SmartReflex
	 * is disabled. Without the SmartReflex bit omap sys_clkreq idle
	 * signal will never trigger for retention idle.
	 */
	if (twl_class_is_4030()) {
		u8 temp;

		twl_i2c_read_u8(TWL4030_MODULE_INTBR, &temp, REG_GPPUPDCTR1);
		temp &= ~(SR_I2C_SDA_CTRL_PU | SR_I2C_SCL_CTRL_PU | \
			I2C_SDA_CTRL_PU | I2C_SCL_CTRL_PU);
		twl_i2c_write_u8(TWL4030_MODULE_INTBR, temp, REG_GPPUPDCTR1);

		twl_i2c_read_u8(TWL_MODULE_PM_RECEIVER, &temp,
				TWL4030_DCDC_GLOBAL_CFG);
		temp |= SMARTREFLEX_ENABLE;
		twl_i2c_write_u8(TWL_MODULE_PM_RECEIVER, temp,
				 TWL4030_DCDC_GLOBAL_CFG);
	}

	if (node) {
		if (pdata)
			twl_auxdata_lookup[0].platform_data = pdata->gpio;
		status = of_platform_populate(node, NULL, twl_auxdata_lookup,
					      &client->dev);
	} else {
		status = add_children(pdata, irq_base, id->driver_data);
	}

fail:
	if (status < 0)
		twl_remove(client);
free:
	if (status < 0)
		platform_device_unregister(pdev);

	return status;
}