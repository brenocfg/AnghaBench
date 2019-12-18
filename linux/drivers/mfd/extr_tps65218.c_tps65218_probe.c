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
struct tps65218 {unsigned int rev; int /*<<< orphan*/  irq_data; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  irq; int /*<<< orphan*/  tps_lock; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int TPS65218_CHIPID_REV_MASK ; 
 int /*<<< orphan*/  TPS65218_REG_CHIPID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct tps65218* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_regmap_add_irq_chip (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tps65218*) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  tps65218_cells ; 
 int /*<<< orphan*/  tps65218_irq_chip ; 
 int /*<<< orphan*/  tps65218_regmap_config ; 
 int tps65218_voltage_set_strict (struct tps65218*) ; 
 int tps65218_voltage_set_uv_hyst (struct tps65218*) ; 
 int tps65218_voltage_set_uvlo (struct tps65218*) ; 

__attribute__((used)) static int tps65218_probe(struct i2c_client *client,
				const struct i2c_device_id *ids)
{
	struct tps65218 *tps;
	int ret;
	unsigned int chipid;

	tps = devm_kzalloc(&client->dev, sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	i2c_set_clientdata(client, tps);
	tps->dev = &client->dev;
	tps->irq = client->irq;
	tps->regmap = devm_regmap_init_i2c(client, &tps65218_regmap_config);
	if (IS_ERR(tps->regmap)) {
		ret = PTR_ERR(tps->regmap);
		dev_err(tps->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	mutex_init(&tps->tps_lock);

	ret = devm_regmap_add_irq_chip(&client->dev, tps->regmap, tps->irq,
				       IRQF_ONESHOT, 0, &tps65218_irq_chip,
				       &tps->irq_data);
	if (ret < 0)
		return ret;

	ret = regmap_read(tps->regmap, TPS65218_REG_CHIPID, &chipid);
	if (ret) {
		dev_err(tps->dev, "Failed to read chipid: %d\n", ret);
		return ret;
	}

	tps->rev = chipid & TPS65218_CHIPID_REV_MASK;

	ret = tps65218_voltage_set_strict(tps);
	if (ret)
		return ret;

	ret = tps65218_voltage_set_uvlo(tps);
	if (ret)
		return ret;

	ret = tps65218_voltage_set_uv_hyst(tps);
	if (ret)
		return ret;

	ret = mfd_add_devices(tps->dev, PLATFORM_DEVID_AUTO, tps65218_cells,
			      ARRAY_SIZE(tps65218_cells), NULL, 0,
			      regmap_irq_get_domain(tps->irq_data));

	return ret;
}