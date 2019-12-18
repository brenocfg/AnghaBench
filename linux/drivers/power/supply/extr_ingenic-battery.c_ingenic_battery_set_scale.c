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
typedef  int u64 ;
struct TYPE_2__ {int voltage_max_design_uv; } ;
struct ingenic_battery {int /*<<< orphan*/  channel; int /*<<< orphan*/  dev; TYPE_1__ info; } ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_AVAIL_LIST ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_SCALE ; 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int iio_read_avail_channel_attribute (int /*<<< orphan*/ ,int const**,int*,int*,int /*<<< orphan*/ ) ; 
 int iio_read_max_channel_raw (int /*<<< orphan*/ ,int*) ; 
 int iio_write_channel_attribute (int /*<<< orphan*/ ,int const,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ingenic_battery_set_scale(struct ingenic_battery *bat)
{
	const int *scale_raw;
	int scale_len, scale_type, best_idx = -1, best_mV, max_raw, i, ret;
	u64 max_mV;

	ret = iio_read_max_channel_raw(bat->channel, &max_raw);
	if (ret) {
		dev_err(bat->dev, "Unable to read max raw channel value\n");
		return ret;
	}

	ret = iio_read_avail_channel_attribute(bat->channel, &scale_raw,
					       &scale_type, &scale_len,
					       IIO_CHAN_INFO_SCALE);
	if (ret < 0) {
		dev_err(bat->dev, "Unable to read channel avail scale\n");
		return ret;
	}
	if (ret != IIO_AVAIL_LIST || scale_type != IIO_VAL_FRACTIONAL_LOG2)
		return -EINVAL;

	max_mV = bat->info.voltage_max_design_uv / 1000;

	for (i = 0; i < scale_len; i += 2) {
		u64 scale_mV = (max_raw * scale_raw[i]) >> scale_raw[i + 1];

		if (scale_mV < max_mV)
			continue;

		if (best_idx >= 0 && scale_mV > best_mV)
			continue;

		best_mV = scale_mV;
		best_idx = i;
	}

	if (best_idx < 0) {
		dev_err(bat->dev, "Unable to find matching voltage scale\n");
		return -EINVAL;
	}

	return iio_write_channel_attribute(bat->channel,
					   scale_raw[best_idx],
					   scale_raw[best_idx + 1],
					   IIO_CHAN_INFO_SCALE);
}