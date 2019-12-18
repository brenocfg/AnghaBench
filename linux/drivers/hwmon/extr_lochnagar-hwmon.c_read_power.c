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
typedef  long u64 ;
struct lochnagar_hwmon {int* power_nsamples; } ;
struct device {int dummy; } ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST_ULL (long,int) ; 
 int /*<<< orphan*/  LN2_CURR ; 
 int LN2_PWR_UNITS ; 
 int /*<<< orphan*/  LN2_VOLT ; 
 long LONG_MAX ; 
 long abs (long) ; 
 struct lochnagar_hwmon* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/ * lochnagar_chan_names ; 
 int read_sensor (struct device*,int,int /*<<< orphan*/ ,int,int,long*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_power(struct device *dev, int chan, long *val)
{
	struct lochnagar_hwmon *priv = dev_get_drvdata(dev);
	int nsamples = priv->power_nsamples[chan];
	u64 power;
	int ret;

	if (!strcmp("SYSVDD", lochnagar_chan_names[chan])) {
		power = 5 * LN2_PWR_UNITS;
	} else {
		ret = read_sensor(dev, chan, LN2_VOLT, 1, LN2_PWR_UNITS, val);
		if (ret < 0)
			return ret;

		power = abs(*val);
	}

	ret = read_sensor(dev, chan, LN2_CURR, nsamples, LN2_PWR_UNITS, val);
	if (ret < 0)
		return ret;

	power *= abs(*val);
	power = DIV_ROUND_CLOSEST_ULL(power, LN2_PWR_UNITS);

	if (power > LONG_MAX)
		*val = LONG_MAX;
	else
		*val = power;

	return 0;
}