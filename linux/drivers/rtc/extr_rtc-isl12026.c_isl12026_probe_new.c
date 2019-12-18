#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nvmem_config {char* name; int stride; int word_size; int size; struct isl12026* priv; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/ * base_dev; } ;
struct isl12026 {TYPE_1__* rtc; int /*<<< orphan*/  nvm_client; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  ISL12026_EEPROM_ADDR ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (TYPE_1__*) ; 
 struct isl12026* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_rtc_allocate_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_new_dummy_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct isl12026*) ; 
 int /*<<< orphan*/  isl12026_force_power_modes (struct i2c_client*) ; 
 int /*<<< orphan*/  isl12026_nvm_read ; 
 int /*<<< orphan*/  isl12026_nvm_write ; 
 int /*<<< orphan*/  isl12026_rtc_ops ; 
 int rtc_nvmem_register (TYPE_1__*,struct nvmem_config*) ; 
 int rtc_register_device (TYPE_1__*) ; 

__attribute__((used)) static int isl12026_probe_new(struct i2c_client *client)
{
	struct isl12026 *priv;
	int ret;
	struct nvmem_config nvm_cfg = {
		.name = "isl12026-",
		.base_dev = &client->dev,
		.stride = 1,
		.word_size = 1,
		.size = 512,
		.reg_read = isl12026_nvm_read,
		.reg_write = isl12026_nvm_write,
	};

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	i2c_set_clientdata(client, priv);

	isl12026_force_power_modes(client);

	priv->nvm_client = i2c_new_dummy_device(client->adapter, ISL12026_EEPROM_ADDR);
	if (IS_ERR(priv->nvm_client))
		return PTR_ERR(priv->nvm_client);

	priv->rtc = devm_rtc_allocate_device(&client->dev);
	ret = PTR_ERR_OR_ZERO(priv->rtc);
	if (ret)
		return ret;

	priv->rtc->ops = &isl12026_rtc_ops;
	nvm_cfg.priv = priv;
	ret = rtc_nvmem_register(priv->rtc, &nvm_cfg);
	if (ret)
		return ret;

	return rtc_register_device(priv->rtc);
}