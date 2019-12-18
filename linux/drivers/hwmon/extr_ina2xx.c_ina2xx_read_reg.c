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
struct ina2xx_data {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int INA2XX_CALIBRATION ; 
 int /*<<< orphan*/  INA2XX_MAX_DELAY ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct ina2xx_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int ina2xx_init (struct ina2xx_data*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 

__attribute__((used)) static int ina2xx_read_reg(struct device *dev, int reg, unsigned int *regval)
{
	struct ina2xx_data *data = dev_get_drvdata(dev);
	int ret, retry;

	dev_dbg(dev, "Starting register %d read\n", reg);

	for (retry = 5; retry; retry--) {

		ret = regmap_read(data->regmap, reg, regval);
		if (ret < 0)
			return ret;

		dev_dbg(dev, "read %d, val = 0x%04x\n", reg, *regval);

		/*
		 * If the current value in the calibration register is 0, the
		 * power and current registers will also remain at 0. In case
		 * the chip has been reset let's check the calibration
		 * register and reinitialize if needed.
		 * We do that extra read of the calibration register if there
		 * is some hint of a chip reset.
		 */
		if (*regval == 0) {
			unsigned int cal;

			ret = regmap_read(data->regmap, INA2XX_CALIBRATION,
					  &cal);
			if (ret < 0)
				return ret;

			if (cal == 0) {
				dev_warn(dev, "chip not calibrated, reinitializing\n");

				ret = ina2xx_init(data);
				if (ret < 0)
					return ret;
				/*
				 * Let's make sure the power and current
				 * registers have been updated before trying
				 * again.
				 */
				msleep(INA2XX_MAX_DELAY);
				continue;
			}
		}
		return 0;
	}

	/*
	 * If we're here then although all write operations succeeded, the
	 * chip still returns 0 in the calibration register. Nothing more we
	 * can do here.
	 */
	dev_err(dev, "unable to reinitialize the chip\n");
	return -ENODEV;
}