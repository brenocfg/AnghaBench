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
struct tps65086 {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPS65086_DEVICEID ; 
 unsigned int TPS65086_DEVICEID_OTP_MASK ; 
 unsigned int TPS65086_DEVICEID_PART_MASK ; 
 unsigned int TPS65086_DEVICEID_REV_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,char,unsigned int) ; 
 struct tps65086* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tps65086*) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  tps65086_cells ; 
 int /*<<< orphan*/  tps65086_irq_chip ; 
 int /*<<< orphan*/  tps65086_regmap_config ; 

__attribute__((used)) static int tps65086_probe(struct i2c_client *client,
			  const struct i2c_device_id *ids)
{
	struct tps65086 *tps;
	unsigned int version;
	int ret;

	tps = devm_kzalloc(&client->dev, sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	i2c_set_clientdata(client, tps);
	tps->dev = &client->dev;
	tps->irq = client->irq;

	tps->regmap = devm_regmap_init_i2c(client, &tps65086_regmap_config);
	if (IS_ERR(tps->regmap)) {
		dev_err(tps->dev, "Failed to initialize register map\n");
		return PTR_ERR(tps->regmap);
	}

	ret = regmap_read(tps->regmap, TPS65086_DEVICEID, &version);
	if (ret) {
		dev_err(tps->dev, "Failed to read revision register\n");
		return ret;
	}

	dev_info(tps->dev, "Device: TPS65086%01lX, OTP: %c, Rev: %ld\n",
		 (version & TPS65086_DEVICEID_PART_MASK),
		 (char)((version & TPS65086_DEVICEID_OTP_MASK) >> 4) + 'A',
		 (version & TPS65086_DEVICEID_REV_MASK) >> 6);

	ret = regmap_add_irq_chip(tps->regmap, tps->irq, IRQF_ONESHOT, 0,
				  &tps65086_irq_chip, &tps->irq_data);
	if (ret) {
		dev_err(tps->dev, "Failed to register IRQ chip\n");
		return ret;
	}

	ret = mfd_add_devices(tps->dev, PLATFORM_DEVID_AUTO, tps65086_cells,
			      ARRAY_SIZE(tps65086_cells), NULL, 0,
			      regmap_irq_get_domain(tps->irq_data));
	if (ret) {
		regmap_del_irq_chip(tps->irq, tps->irq_data);
		return ret;
	}

	return 0;
}