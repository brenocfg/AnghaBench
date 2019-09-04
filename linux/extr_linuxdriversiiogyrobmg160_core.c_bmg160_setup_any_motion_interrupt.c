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
struct bmg160_data {int slope_thres; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dready_trigger_on; } ;

/* Variables and functions */
 int BMG160_DATA_ENABLE_INT ; 
 int /*<<< orphan*/  BMG160_INT_MAP_0_BIT_ANY ; 
 int BMG160_INT_MODE_LATCH_INT ; 
 int BMG160_INT_MODE_LATCH_RESET ; 
 int BMG160_INT_MOTION_X ; 
 int BMG160_INT_MOTION_Y ; 
 int BMG160_INT_MOTION_Z ; 
 int /*<<< orphan*/  BMG160_REG_INT_EN_0 ; 
 int /*<<< orphan*/  BMG160_REG_INT_MAP_0 ; 
 int /*<<< orphan*/  BMG160_REG_INT_RST_LATCH ; 
 int /*<<< orphan*/  BMG160_REG_MOTION_INTR ; 
 int /*<<< orphan*/  BMG160_REG_SLOPE_THRES ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bmg160_setup_any_motion_interrupt(struct bmg160_data *data,
					     bool status)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;

	/* Enable/Disable INT_MAP0 mapping */
	ret = regmap_update_bits(data->regmap, BMG160_REG_INT_MAP_0,
				 BMG160_INT_MAP_0_BIT_ANY,
				 (status ? BMG160_INT_MAP_0_BIT_ANY : 0));
	if (ret < 0) {
		dev_err(dev, "Error updating bits reg_int_map0\n");
		return ret;
	}

	/* Enable/Disable slope interrupts */
	if (status) {
		/* Update slope thres */
		ret = regmap_write(data->regmap, BMG160_REG_SLOPE_THRES,
				   data->slope_thres);
		if (ret < 0) {
			dev_err(dev, "Error writing reg_slope_thres\n");
			return ret;
		}

		ret = regmap_write(data->regmap, BMG160_REG_MOTION_INTR,
				   BMG160_INT_MOTION_X | BMG160_INT_MOTION_Y |
				   BMG160_INT_MOTION_Z);
		if (ret < 0) {
			dev_err(dev, "Error writing reg_motion_intr\n");
			return ret;
		}

		/*
		 * New data interrupt is always non-latched,
		 * which will have higher priority, so no need
		 * to set latched mode, we will be flooded anyway with INTR
		 */
		if (!data->dready_trigger_on) {
			ret = regmap_write(data->regmap,
					   BMG160_REG_INT_RST_LATCH,
					   BMG160_INT_MODE_LATCH_INT |
					   BMG160_INT_MODE_LATCH_RESET);
			if (ret < 0) {
				dev_err(dev, "Error writing reg_rst_latch\n");
				return ret;
			}
		}

		ret = regmap_write(data->regmap, BMG160_REG_INT_EN_0,
				   BMG160_DATA_ENABLE_INT);

	} else {
		ret = regmap_write(data->regmap, BMG160_REG_INT_EN_0, 0);
	}

	if (ret < 0) {
		dev_err(dev, "Error writing reg_int_en0\n");
		return ret;
	}

	return 0;
}