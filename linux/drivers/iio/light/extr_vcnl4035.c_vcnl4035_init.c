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
struct vcnl4035_data {int als_it_val; int als_persistence; void* als_thresh_low; TYPE_1__* client; int /*<<< orphan*/  regmap; void* als_thresh_high; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  VCNL4035_ALS_CONF ; 
 int VCNL4035_ALS_IT_DEFAULT ; 
 int /*<<< orphan*/  VCNL4035_ALS_IT_MASK ; 
 int VCNL4035_ALS_PERS_DEFAULT ; 
 int /*<<< orphan*/  VCNL4035_ALS_PERS_MASK ; 
 int /*<<< orphan*/  VCNL4035_ALS_THDH ; 
 void* VCNL4035_ALS_THDH_DEFAULT ; 
 int /*<<< orphan*/  VCNL4035_ALS_THDL ; 
 void* VCNL4035_ALS_THDL_DEFAULT ; 
 int /*<<< orphan*/  VCNL4035_DEV_ID ; 
 int VCNL4035_DEV_ID_VAL ; 
 int /*<<< orphan*/  VCNL4035_MODE_ALS_ENABLE ; 
 int /*<<< orphan*/  VCNL4035_MODE_ALS_WHITE_CHAN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int vcnl4035_set_als_power_state (struct vcnl4035_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vcnl4035_init(struct vcnl4035_data *data)
{
	int ret;
	int id;

	ret = regmap_read(data->regmap, VCNL4035_DEV_ID, &id);
	if (ret < 0) {
		dev_err(&data->client->dev, "Failed to read DEV_ID register\n");
		return ret;
	}

	if (id != VCNL4035_DEV_ID_VAL) {
		dev_err(&data->client->dev, "Wrong id, got %x, expected %x\n",
			id, VCNL4035_DEV_ID_VAL);
		return -ENODEV;
	}

	ret = vcnl4035_set_als_power_state(data, VCNL4035_MODE_ALS_ENABLE);
	if (ret < 0)
		return ret;

	/* ALS white channel enable */
	ret = regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
				 VCNL4035_MODE_ALS_WHITE_CHAN,
				 1);
	if (ret) {
		dev_err(&data->client->dev, "set white channel enable %d\n",
			ret);
		return ret;
	}

	/* set default integration time - 100 ms for ALS */
	ret = regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
				 VCNL4035_ALS_IT_MASK,
				 VCNL4035_ALS_IT_DEFAULT);
	if (ret) {
		dev_err(&data->client->dev, "set default ALS IT returned %d\n",
			ret);
		return ret;
	}
	data->als_it_val = VCNL4035_ALS_IT_DEFAULT;

	/* set default persistence time - 1 for ALS */
	ret = regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
				 VCNL4035_ALS_PERS_MASK,
				 VCNL4035_ALS_PERS_DEFAULT);
	if (ret) {
		dev_err(&data->client->dev, "set default PERS returned %d\n",
			ret);
		return ret;
	}
	data->als_persistence = VCNL4035_ALS_PERS_DEFAULT;

	/* set default HIGH threshold for ALS */
	ret = regmap_write(data->regmap, VCNL4035_ALS_THDH,
				VCNL4035_ALS_THDH_DEFAULT);
	if (ret) {
		dev_err(&data->client->dev, "set default THDH returned %d\n",
			ret);
		return ret;
	}
	data->als_thresh_high = VCNL4035_ALS_THDH_DEFAULT;

	/* set default LOW threshold for ALS */
	ret = regmap_write(data->regmap, VCNL4035_ALS_THDL,
				VCNL4035_ALS_THDL_DEFAULT);
	if (ret) {
		dev_err(&data->client->dev, "set default THDL returned %d\n",
			ret);
		return ret;
	}
	data->als_thresh_low = VCNL4035_ALS_THDL_DEFAULT;

	return 0;
}