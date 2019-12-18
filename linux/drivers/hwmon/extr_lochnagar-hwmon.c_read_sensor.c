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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct lochnagar_hwmon {int /*<<< orphan*/  sensor_lock; struct regmap* regmap; } ;
struct device {int dummy; } ;
typedef  enum lochnagar_measure_mode { ____Placeholder_lochnagar_measure_mode } lochnagar_measure_mode ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct lochnagar_hwmon* dev_get_drvdata (struct device*) ; 
 int do_measurement (struct regmap*,int,int,int) ; 
 long float_to_long (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int request_data (struct regmap*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_sensor(struct device *dev, int chan,
		       enum lochnagar_measure_mode mode, int nsamples,
		       unsigned int precision, long *val)
{
	struct lochnagar_hwmon *priv = dev_get_drvdata(dev);
	struct regmap *regmap = priv->regmap;
	u32 data;
	int ret;

	mutex_lock(&priv->sensor_lock);

	ret = do_measurement(regmap, chan, mode, nsamples);
	if (ret < 0) {
		dev_err(dev, "Failed to perform measurement: %d\n", ret);
		goto error;
	}

	ret = request_data(regmap, chan, &data);
	if (ret < 0) {
		dev_err(dev, "Failed to read measurement: %d\n", ret);
		goto error;
	}

	*val = float_to_long(data, precision);

error:
	mutex_unlock(&priv->sensor_lock);

	return ret;
}