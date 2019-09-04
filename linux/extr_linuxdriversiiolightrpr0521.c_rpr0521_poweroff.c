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
struct rpr0521_data {int als_dev_en; int pxs_dev_en; TYPE_1__* client; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RPR0521_MODE_ALS_DISABLE ; 
 int RPR0521_MODE_ALS_MASK ; 
 int RPR0521_MODE_PXS_DISABLE ; 
 int RPR0521_MODE_PXS_MASK ; 
 int /*<<< orphan*/  RPR0521_REG_INTERRUPT ; 
 int /*<<< orphan*/  RPR0521_REG_MODE_CTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int rpr0521_poweroff(struct rpr0521_data *data)
{
	int ret;
	int tmp;

	ret = regmap_update_bits(data->regmap, RPR0521_REG_MODE_CTRL,
				 RPR0521_MODE_ALS_MASK |
				 RPR0521_MODE_PXS_MASK,
				 RPR0521_MODE_ALS_DISABLE |
				 RPR0521_MODE_PXS_DISABLE);
	if (ret < 0)
		return ret;

	data->als_dev_en = false;
	data->pxs_dev_en = false;

	/*
	 * Int pin keeps state after power off. Set pin to high impedance
	 * mode to prevent power drain.
	 */
	ret = regmap_read(data->regmap, RPR0521_REG_INTERRUPT, &tmp);
	if (ret) {
		dev_err(&data->client->dev, "Failed to reset int pin.\n");
		return ret;
	}

	return 0;
}