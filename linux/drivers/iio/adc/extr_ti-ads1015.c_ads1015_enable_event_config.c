#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int realbits; int shift; } ;
struct iio_chan_spec {size_t address; TYPE_2__ scan_type; } ;
struct ads1015_data {size_t event_channel; int comp_mode; int /*<<< orphan*/  regmap; TYPE_1__* thresh_data; } ;
struct TYPE_3__ {int low_thresh; int high_thresh; } ;

/* Variables and functions */
 int ADS1015_CFG_COMP_MODE_TRAD ; 
 int ADS1015_CFG_COMP_MODE_WINDOW ; 
 int /*<<< orphan*/  ADS1015_HI_THRESH_REG ; 
 int /*<<< orphan*/  ADS1015_LO_THRESH_REG ; 
 int EBUSY ; 
 int /*<<< orphan*/  ads1015_event_channel_disable (struct ads1015_data*,size_t) ; 
 int /*<<< orphan*/  ads1015_event_channel_enable (struct ads1015_data*,size_t,int) ; 
 scalar_t__ ads1015_event_channel_enabled (struct ads1015_data*) ; 
 int ads1015_get_adc_result (struct ads1015_data*,size_t,unsigned int*) ; 
 int ads1015_set_power_state (struct ads1015_data*,int) ; 
 int max (int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ads1015_enable_event_config(struct ads1015_data *data,
	const struct iio_chan_spec *chan, int comp_mode)
{
	int low_thresh = data->thresh_data[chan->address].low_thresh;
	int high_thresh = data->thresh_data[chan->address].high_thresh;
	int ret;
	unsigned int val;

	if (ads1015_event_channel_enabled(data)) {
		if (data->event_channel != chan->address ||
			(data->comp_mode == ADS1015_CFG_COMP_MODE_TRAD &&
				comp_mode == ADS1015_CFG_COMP_MODE_WINDOW))
			return -EBUSY;

		return 0;
	}

	if (comp_mode == ADS1015_CFG_COMP_MODE_TRAD) {
		low_thresh = max(-1 << (chan->scan_type.realbits - 1),
				high_thresh - 1);
	}
	ret = regmap_write(data->regmap, ADS1015_LO_THRESH_REG,
			low_thresh << chan->scan_type.shift);
	if (ret)
		return ret;

	ret = regmap_write(data->regmap, ADS1015_HI_THRESH_REG,
			high_thresh << chan->scan_type.shift);
	if (ret)
		return ret;

	ret = ads1015_set_power_state(data, true);
	if (ret < 0)
		return ret;

	ads1015_event_channel_enable(data, chan->address, comp_mode);

	ret = ads1015_get_adc_result(data, chan->address, &val);
	if (ret) {
		ads1015_event_channel_disable(data, chan->address);
		ads1015_set_power_state(data, false);
	}

	return ret;
}