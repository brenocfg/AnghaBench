#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;
struct adv7511_link_config {int dummy; } ;
struct TYPE_12__ {scalar_t__ of_node; int /*<<< orphan*/ * funcs; } ;
struct adv7511 {int powered; int type; TYPE_1__* i2c_edid; TYPE_1__* i2c_packet; scalar_t__ cec_clk; TYPE_1__* i2c_cec; TYPE_6__ bridge; int /*<<< orphan*/  wq; int /*<<< orphan*/  hpd_work; TYPE_1__* regmap; TYPE_1__* gpio_pd; int /*<<< orphan*/  status; struct i2c_client* i2c_main; } ;
typedef  int /*<<< orphan*/  link_config ;
typedef  enum adv7511_type { ____Placeholder_adv7511_type } adv7511_type ;
struct TYPE_11__ {int addr; } ;

/* Variables and functions */
 scalar_t__ ADV7511 ; 
 int /*<<< orphan*/  ADV7511_EDID_I2C_ADDR_DEFAULT ; 
 int /*<<< orphan*/  ADV7511_PACKET_I2C_ADDR_DEFAULT ; 
 int /*<<< orphan*/  ADV7511_REG_CEC_I2C_ADDR ; 
 int /*<<< orphan*/  ADV7511_REG_CHIP_REVISION ; 
 int /*<<< orphan*/  ADV7511_REG_EDID_I2C_ADDR ; 
 int /*<<< orphan*/  ADV7511_REG_PACKET_I2C_ADDR ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  adv7511_audio_init (struct device*,struct adv7511*) ; 
 int /*<<< orphan*/  adv7511_bridge_funcs ; 
 int adv7511_cec_init (struct device*,struct adv7511*) ; 
 int /*<<< orphan*/  adv7511_fixed_registers ; 
 int /*<<< orphan*/  adv7511_hpd_work ; 
 int adv7511_init_cec_regmap (struct adv7511*) ; 
 int adv7511_init_regulators (struct adv7511*) ; 
 int /*<<< orphan*/  adv7511_irq_handler ; 
 int /*<<< orphan*/  adv7511_packet_disable (struct adv7511*,int) ; 
 int adv7511_parse_dt (scalar_t__,struct adv7511_link_config*) ; 
 int /*<<< orphan*/  adv7511_power_off (struct adv7511*) ; 
 int /*<<< orphan*/  adv7511_regmap_config ; 
 int /*<<< orphan*/  adv7511_set_link_config (struct adv7511*,struct adv7511_link_config*) ; 
 int /*<<< orphan*/  adv7511_uninit_regulators (struct adv7511*) ; 
 int adv7533_parse_dt (scalar_t__,struct adv7511*) ; 
 int adv7533_patch_registers (struct adv7511*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  connector_status_disconnected ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 TYPE_1__* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct adv7511* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct adv7511*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_6__*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* i2c_new_ancillary_device (struct i2c_client*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adv7511*) ; 
 int /*<<< orphan*/  i2c_unregister_device (TYPE_1__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct adv7511_link_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int regmap_read (TYPE_1__*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_register_patch (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int adv7511_probe(struct i2c_client *i2c, const struct i2c_device_id *id)
{
	struct adv7511_link_config link_config;
	struct adv7511 *adv7511;
	struct device *dev = &i2c->dev;
	unsigned int val;
	int ret;

	if (!dev->of_node)
		return -EINVAL;

	adv7511 = devm_kzalloc(dev, sizeof(*adv7511), GFP_KERNEL);
	if (!adv7511)
		return -ENOMEM;

	adv7511->i2c_main = i2c;
	adv7511->powered = false;
	adv7511->status = connector_status_disconnected;

	if (dev->of_node)
		adv7511->type = (enum adv7511_type)of_device_get_match_data(dev);
	else
		adv7511->type = id->driver_data;

	memset(&link_config, 0, sizeof(link_config));

	if (adv7511->type == ADV7511)
		ret = adv7511_parse_dt(dev->of_node, &link_config);
	else
		ret = adv7533_parse_dt(dev->of_node, adv7511);
	if (ret)
		return ret;

	ret = adv7511_init_regulators(adv7511);
	if (ret) {
		dev_err(dev, "failed to init regulators\n");
		return ret;
	}

	/*
	 * The power down GPIO is optional. If present, toggle it from active to
	 * inactive to wake up the encoder.
	 */
	adv7511->gpio_pd = devm_gpiod_get_optional(dev, "pd", GPIOD_OUT_HIGH);
	if (IS_ERR(adv7511->gpio_pd)) {
		ret = PTR_ERR(adv7511->gpio_pd);
		goto uninit_regulators;
	}

	if (adv7511->gpio_pd) {
		usleep_range(5000, 6000);
		gpiod_set_value_cansleep(adv7511->gpio_pd, 0);
	}

	adv7511->regmap = devm_regmap_init_i2c(i2c, &adv7511_regmap_config);
	if (IS_ERR(adv7511->regmap)) {
		ret = PTR_ERR(adv7511->regmap);
		goto uninit_regulators;
	}

	ret = regmap_read(adv7511->regmap, ADV7511_REG_CHIP_REVISION, &val);
	if (ret)
		goto uninit_regulators;
	dev_dbg(dev, "Rev. %d\n", val);

	if (adv7511->type == ADV7511)
		ret = regmap_register_patch(adv7511->regmap,
					    adv7511_fixed_registers,
					    ARRAY_SIZE(adv7511_fixed_registers));
	else
		ret = adv7533_patch_registers(adv7511);
	if (ret)
		goto uninit_regulators;

	adv7511_packet_disable(adv7511, 0xffff);

	adv7511->i2c_edid = i2c_new_ancillary_device(i2c, "edid",
					ADV7511_EDID_I2C_ADDR_DEFAULT);
	if (IS_ERR(adv7511->i2c_edid)) {
		ret = PTR_ERR(adv7511->i2c_edid);
		goto uninit_regulators;
	}

	regmap_write(adv7511->regmap, ADV7511_REG_EDID_I2C_ADDR,
		     adv7511->i2c_edid->addr << 1);

	adv7511->i2c_packet = i2c_new_ancillary_device(i2c, "packet",
					ADV7511_PACKET_I2C_ADDR_DEFAULT);
	if (IS_ERR(adv7511->i2c_packet)) {
		ret = PTR_ERR(adv7511->i2c_packet);
		goto err_i2c_unregister_edid;
	}

	regmap_write(adv7511->regmap, ADV7511_REG_PACKET_I2C_ADDR,
		     adv7511->i2c_packet->addr << 1);

	ret = adv7511_init_cec_regmap(adv7511);
	if (ret)
		goto err_i2c_unregister_packet;

	regmap_write(adv7511->regmap, ADV7511_REG_CEC_I2C_ADDR,
		     adv7511->i2c_cec->addr << 1);

	INIT_WORK(&adv7511->hpd_work, adv7511_hpd_work);

	if (i2c->irq) {
		init_waitqueue_head(&adv7511->wq);

		ret = devm_request_threaded_irq(dev, i2c->irq, NULL,
						adv7511_irq_handler,
						IRQF_ONESHOT, dev_name(dev),
						adv7511);
		if (ret)
			goto err_unregister_cec;
	}

	adv7511_power_off(adv7511);

	i2c_set_clientdata(i2c, adv7511);

	if (adv7511->type == ADV7511)
		adv7511_set_link_config(adv7511, &link_config);

	ret = adv7511_cec_init(dev, adv7511);
	if (ret)
		goto err_unregister_cec;

	adv7511->bridge.funcs = &adv7511_bridge_funcs;
	adv7511->bridge.of_node = dev->of_node;

	drm_bridge_add(&adv7511->bridge);

	adv7511_audio_init(dev, adv7511);
	return 0;

err_unregister_cec:
	i2c_unregister_device(adv7511->i2c_cec);
	if (adv7511->cec_clk)
		clk_disable_unprepare(adv7511->cec_clk);
err_i2c_unregister_packet:
	i2c_unregister_device(adv7511->i2c_packet);
err_i2c_unregister_edid:
	i2c_unregister_device(adv7511->i2c_edid);
uninit_regulators:
	adv7511_uninit_regulators(adv7511);

	return ret;
}