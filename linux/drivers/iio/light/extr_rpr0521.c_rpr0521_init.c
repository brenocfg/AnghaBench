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
struct rpr0521_data {scalar_t__ irq_timestamp; int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RPR0521_DEFAULT_MEAS_TIME ; 
 int RPR0521_MANUFACT_ID ; 
 int /*<<< orphan*/  RPR0521_MODE_ALS_ENABLE ; 
 int /*<<< orphan*/  RPR0521_MODE_MEAS_TIME_MASK ; 
 int /*<<< orphan*/  RPR0521_MODE_PXS_ENABLE ; 
 int /*<<< orphan*/  RPR0521_REG_ID ; 
 int /*<<< orphan*/  RPR0521_REG_MODE_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rpr0521_als_enable (struct rpr0521_data*,int /*<<< orphan*/ ) ; 
 int rpr0521_pxs_enable (struct rpr0521_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpr0521_init(struct rpr0521_data *data)
{
	int ret;
	int id;

	ret = regmap_read(data->regmap, RPR0521_REG_ID, &id);
	if (ret < 0) {
		dev_err(&data->client->dev, "Failed to read REG_ID register\n");
		return ret;
	}

	if (id != RPR0521_MANUFACT_ID) {
		dev_err(&data->client->dev, "Wrong id, got %x, expected %x\n",
			id, RPR0521_MANUFACT_ID);
		return -ENODEV;
	}

	/* set default measurement time - 100 ms for both ALS and PS */
	ret = regmap_update_bits(data->regmap, RPR0521_REG_MODE_CTRL,
				 RPR0521_MODE_MEAS_TIME_MASK,
				 RPR0521_DEFAULT_MEAS_TIME);
	if (ret) {
		pr_err("regmap_update_bits returned %d\n", ret);
		return ret;
	}

#ifndef CONFIG_PM
	ret = rpr0521_als_enable(data, RPR0521_MODE_ALS_ENABLE);
	if (ret < 0)
		return ret;
	ret = rpr0521_pxs_enable(data, RPR0521_MODE_PXS_ENABLE);
	if (ret < 0)
		return ret;
#endif

	data->irq_timestamp = 0;

	return 0;
}