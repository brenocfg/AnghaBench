#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/ * funcs; } ;
struct sii902x {TYPE_1__ bridge; int /*<<< orphan*/  regmap; int /*<<< orphan*/  reset_gpio; struct i2c_client* i2c; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int SII902X_HOTPLUG_EVENT ; 
 int /*<<< orphan*/  SII902X_INT_ENABLE ; 
 int /*<<< orphan*/  SII902X_INT_STATUS ; 
 int /*<<< orphan*/  SII902X_REG_CHIPID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SII902X_REG_TPI_RQB ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct sii902x* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sii902x*) ; 
 int /*<<< orphan*/  drm_bridge_add (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sii902x*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sii902x_bridge_funcs ; 
 int /*<<< orphan*/  sii902x_interrupt ; 
 int /*<<< orphan*/  sii902x_regmap_config ; 
 int /*<<< orphan*/  sii902x_reset (struct sii902x*) ; 

__attribute__((used)) static int sii902x_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	unsigned int status = 0;
	struct sii902x *sii902x;
	u8 chipid[4];
	int ret;

	sii902x = devm_kzalloc(dev, sizeof(*sii902x), GFP_KERNEL);
	if (!sii902x)
		return -ENOMEM;

	sii902x->i2c = client;
	sii902x->regmap = devm_regmap_init_i2c(client, &sii902x_regmap_config);
	if (IS_ERR(sii902x->regmap))
		return PTR_ERR(sii902x->regmap);

	sii902x->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						      GPIOD_OUT_LOW);
	if (IS_ERR(sii902x->reset_gpio)) {
		dev_err(dev, "Failed to retrieve/request reset gpio: %ld\n",
			PTR_ERR(sii902x->reset_gpio));
		return PTR_ERR(sii902x->reset_gpio);
	}

	sii902x_reset(sii902x);

	ret = regmap_write(sii902x->regmap, SII902X_REG_TPI_RQB, 0x0);
	if (ret)
		return ret;

	ret = regmap_bulk_read(sii902x->regmap, SII902X_REG_CHIPID(0),
			       &chipid, 4);
	if (ret) {
		dev_err(dev, "regmap_read failed %d\n", ret);
		return ret;
	}

	if (chipid[0] != 0xb0) {
		dev_err(dev, "Invalid chipid: %02x (expecting 0xb0)\n",
			chipid[0]);
		return -EINVAL;
	}

	/* Clear all pending interrupts */
	regmap_read(sii902x->regmap, SII902X_INT_STATUS, &status);
	regmap_write(sii902x->regmap, SII902X_INT_STATUS, status);

	if (client->irq > 0) {
		regmap_write(sii902x->regmap, SII902X_INT_ENABLE,
			     SII902X_HOTPLUG_EVENT);

		ret = devm_request_threaded_irq(dev, client->irq, NULL,
						sii902x_interrupt,
						IRQF_ONESHOT, dev_name(dev),
						sii902x);
		if (ret)
			return ret;
	}

	sii902x->bridge.funcs = &sii902x_bridge_funcs;
	sii902x->bridge.of_node = dev->of_node;
	drm_bridge_add(&sii902x->bridge);

	i2c_set_clientdata(client, sii902x);

	return 0;
}