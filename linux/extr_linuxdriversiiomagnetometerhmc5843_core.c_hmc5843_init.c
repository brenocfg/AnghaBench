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
typedef  char u8 ;
struct hmc5843_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  HMC5843_ID_REG ; 
 int /*<<< orphan*/  HMC5843_MEAS_CONF_NORMAL ; 
 int /*<<< orphan*/  HMC5843_MODE_CONVERSION_CONTINUOUS ; 
 int /*<<< orphan*/  HMC5843_RANGE_GAIN_DEFAULT ; 
 int /*<<< orphan*/  HMC5843_RATE_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hmc5843_set_meas_conf (struct hmc5843_data*,int /*<<< orphan*/ ) ; 
 int hmc5843_set_mode (struct hmc5843_data*,int /*<<< orphan*/ ) ; 
 int hmc5843_set_range_gain (struct hmc5843_data*,int /*<<< orphan*/ ) ; 
 int hmc5843_set_samp_freq (struct hmc5843_data*,int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hmc5843_init(struct hmc5843_data *data)
{
	int ret;
	u8 id[3];

	ret = regmap_bulk_read(data->regmap, HMC5843_ID_REG,
			       id, ARRAY_SIZE(id));
	if (ret < 0)
		return ret;
	if (id[0] != 'H' || id[1] != '4' || id[2] != '3') {
		dev_err(data->dev, "no HMC5843/5883/5883L/5983 sensor\n");
		return -ENODEV;
	}

	ret = hmc5843_set_meas_conf(data, HMC5843_MEAS_CONF_NORMAL);
	if (ret < 0)
		return ret;
	ret = hmc5843_set_samp_freq(data, HMC5843_RATE_DEFAULT);
	if (ret < 0)
		return ret;
	ret = hmc5843_set_range_gain(data, HMC5843_RANGE_GAIN_DEFAULT);
	if (ret < 0)
		return ret;
	return hmc5843_set_mode(data, HMC5843_MODE_CONVERSION_CONTINUOUS);
}