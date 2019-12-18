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
struct device {int dummy; } ;
struct atlas_data {int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATLAS_REG_PH_CALIB_STATUS ; 
 unsigned int ATLAS_REG_PH_CALIB_STATUS_HIGH ; 
 unsigned int ATLAS_REG_PH_CALIB_STATUS_LOW ; 
 unsigned int ATLAS_REG_PH_CALIB_STATUS_MASK ; 
 unsigned int ATLAS_REG_PH_CALIB_STATUS_MID ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int atlas_check_ph_calibration(struct atlas_data *data)
{
	struct device *dev = &data->client->dev;
	int ret;
	unsigned int val;

	ret = regmap_read(data->regmap, ATLAS_REG_PH_CALIB_STATUS, &val);
	if (ret)
		return ret;

	if (!(val & ATLAS_REG_PH_CALIB_STATUS_MASK)) {
		dev_warn(dev, "device has not been calibrated\n");
		return 0;
	}

	if (!(val & ATLAS_REG_PH_CALIB_STATUS_LOW))
		dev_warn(dev, "device missing low point calibration\n");

	if (!(val & ATLAS_REG_PH_CALIB_STATUS_MID))
		dev_warn(dev, "device missing mid point calibration\n");

	if (!(val & ATLAS_REG_PH_CALIB_STATUS_HIGH))
		dev_warn(dev, "device missing high point calibration\n");

	return 0;
}