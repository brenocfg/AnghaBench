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
struct iio_chan_spec {scalar_t__ address; } ;
struct ads1015_data {scalar_t__ event_channel; scalar_t__ comp_mode; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ADS1015_CFG_COMP_DISABLE ; 
 scalar_t__ ADS1015_CFG_COMP_MODE_TRAD ; 
 int ADS1015_CFG_COMP_MODE_WINDOW ; 
 int /*<<< orphan*/  ADS1015_CFG_COMP_QUE_MASK ; 
 int ADS1015_CFG_COMP_QUE_SHIFT ; 
 int /*<<< orphan*/  ADS1015_CFG_REG ; 
 int /*<<< orphan*/  ads1015_event_channel_disable (struct ads1015_data*,scalar_t__) ; 
 int /*<<< orphan*/  ads1015_event_channel_enabled (struct ads1015_data*) ; 
 int ads1015_set_power_state (struct ads1015_data*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ads1015_disable_event_config(struct ads1015_data *data,
	const struct iio_chan_spec *chan, int comp_mode)
{
	int ret;

	if (!ads1015_event_channel_enabled(data))
		return 0;

	if (data->event_channel != chan->address)
		return 0;

	if (data->comp_mode == ADS1015_CFG_COMP_MODE_TRAD &&
			comp_mode == ADS1015_CFG_COMP_MODE_WINDOW)
		return 0;

	ret = regmap_update_bits(data->regmap, ADS1015_CFG_REG,
				ADS1015_CFG_COMP_QUE_MASK,
				ADS1015_CFG_COMP_DISABLE <<
					ADS1015_CFG_COMP_QUE_SHIFT);
	if (ret)
		return ret;

	ads1015_event_channel_disable(data, chan->address);

	return ads1015_set_power_state(data, false);
}