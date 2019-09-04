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
struct device {int dummy; } ;
struct bmc150_accel_data {int /*<<< orphan*/  slope_dur; int /*<<< orphan*/  slope_thres; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_ACCEL_REG_INT_5 ; 
 int /*<<< orphan*/  BMC150_ACCEL_REG_INT_6 ; 
 int /*<<< orphan*/  BMC150_ACCEL_SLOPE_DUR_MASK ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bmc150_accel_update_slope(struct bmc150_accel_data *data)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;

	ret = regmap_write(data->regmap, BMC150_ACCEL_REG_INT_6,
					data->slope_thres);
	if (ret < 0) {
		dev_err(dev, "Error writing reg_int_6\n");
		return ret;
	}

	ret = regmap_update_bits(data->regmap, BMC150_ACCEL_REG_INT_5,
				 BMC150_ACCEL_SLOPE_DUR_MASK, data->slope_dur);
	if (ret < 0) {
		dev_err(dev, "Error updating reg_int_5\n");
		return ret;
	}

	dev_dbg(dev, "%x %x\n", data->slope_thres, data->slope_dur);

	return ret;
}