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
struct smsc {int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; TYPE_1__* dev; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMSC_CLK_CTRL ; 
 int /*<<< orphan*/  SMSC_DEV_ID ; 
 int /*<<< orphan*/  SMSC_DEV_REV ; 
 int /*<<< orphan*/  SMSC_VEN_ID_H ; 
 int /*<<< orphan*/  SMSC_VEN_ID_L ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int,int,int) ; 
 struct smsc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct smsc*) ; 
 int /*<<< orphan*/  of_property_read_u32 (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc_regmap_config ; 

__attribute__((used)) static int smsc_i2c_probe(struct i2c_client *i2c,
			const struct i2c_device_id *id)
{
	struct smsc *smsc;
	int devid, rev, venid_l, venid_h;
	int ret;

	smsc = devm_kzalloc(&i2c->dev, sizeof(*smsc), GFP_KERNEL);
	if (!smsc)
		return -ENOMEM;

	smsc->regmap = devm_regmap_init_i2c(i2c, &smsc_regmap_config);
	if (IS_ERR(smsc->regmap))
		return PTR_ERR(smsc->regmap);

	i2c_set_clientdata(i2c, smsc);
	smsc->dev = &i2c->dev;

#ifdef CONFIG_OF
	of_property_read_u32(i2c->dev.of_node, "clock", &smsc->clk);
#endif

	regmap_read(smsc->regmap, SMSC_DEV_ID, &devid);
	regmap_read(smsc->regmap, SMSC_DEV_REV, &rev);
	regmap_read(smsc->regmap, SMSC_VEN_ID_L, &venid_l);
	regmap_read(smsc->regmap, SMSC_VEN_ID_H, &venid_h);

	dev_info(&i2c->dev, "SMSCxxx devid: %02x rev: %02x venid: %02x\n",
		devid, rev, (venid_h << 8) | venid_l);

	ret = regmap_write(smsc->regmap, SMSC_CLK_CTRL, smsc->clk);
	if (ret)
		return ret;

#ifdef CONFIG_OF
	if (i2c->dev.of_node)
		ret = devm_of_platform_populate(&i2c->dev);
#endif

	return ret;
}