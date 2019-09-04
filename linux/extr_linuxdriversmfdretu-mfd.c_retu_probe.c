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
struct retu_dev {int /*<<< orphan*/  irq_data; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  mutex; } ;
struct retu_data {char* companion_name; int /*<<< orphan*/  nchildren; int /*<<< orphan*/  children; TYPE_1__* irq_chip; int /*<<< orphan*/  chip_name; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask_base; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct retu_data*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETU_REG_ASICR ; 
 int RETU_REG_ASICR_VILMA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,char*,int,int) ; 
 struct retu_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct retu_dev*) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_power_off ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_irq_chip_get_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retu_bus ; 
 int /*<<< orphan*/  retu_config ; 
 struct retu_data* retu_data ; 
 struct retu_dev* retu_pm_power_off ; 
 scalar_t__ retu_power_off ; 
 int retu_read (struct retu_dev*,int /*<<< orphan*/ ) ; 
 int retu_write (struct retu_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int retu_probe(struct i2c_client *i2c, const struct i2c_device_id *id)
{
	struct retu_data const *rdat;
	struct retu_dev *rdev;
	int ret;

	if (i2c->addr > ARRAY_SIZE(retu_data))
		return -ENODEV;
	rdat = &retu_data[i2c->addr - 1];

	rdev = devm_kzalloc(&i2c->dev, sizeof(*rdev), GFP_KERNEL);
	if (rdev == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, rdev);
	rdev->dev = &i2c->dev;
	mutex_init(&rdev->mutex);
	rdev->regmap = devm_regmap_init(&i2c->dev, &retu_bus, &i2c->dev,
					&retu_config);
	if (IS_ERR(rdev->regmap))
		return PTR_ERR(rdev->regmap);

	ret = retu_read(rdev, RETU_REG_ASICR);
	if (ret < 0) {
		dev_err(rdev->dev, "could not read %s revision: %d\n",
			rdat->chip_name, ret);
		return ret;
	}

	dev_info(rdev->dev, "%s%s%s v%d.%d found\n", rdat->chip_name,
		 (ret & RETU_REG_ASICR_VILMA) ? " & " : "",
		 (ret & RETU_REG_ASICR_VILMA) ? rdat->companion_name : "",
		 (ret >> 4) & 0x7, ret & 0xf);

	/* Mask all interrupts. */
	ret = retu_write(rdev, rdat->irq_chip->mask_base, 0xffff);
	if (ret < 0)
		return ret;

	ret = regmap_add_irq_chip(rdev->regmap, i2c->irq, IRQF_ONESHOT, -1,
				  rdat->irq_chip, &rdev->irq_data);
	if (ret < 0)
		return ret;

	ret = mfd_add_devices(rdev->dev, -1, rdat->children, rdat->nchildren,
			      NULL, regmap_irq_chip_get_base(rdev->irq_data),
			      NULL);
	if (ret < 0) {
		regmap_del_irq_chip(i2c->irq, rdev->irq_data);
		return ret;
	}

	if (i2c->addr == 1 && !pm_power_off) {
		retu_pm_power_off = rdev;
		pm_power_off	  = retu_power_off;
	}

	return 0;
}