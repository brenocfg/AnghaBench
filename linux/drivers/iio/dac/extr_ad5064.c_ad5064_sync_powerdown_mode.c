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
struct iio_chan_spec {unsigned int address; size_t channel; } ;
struct ad5064_state {unsigned int* pwr_down_mode; scalar_t__* pwr_down; TYPE_1__* chip_info; } ;
struct TYPE_2__ {scalar_t__ regmap_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5064_CMD_POWERDOWN_DAC ; 
 scalar_t__ AD5064_REGMAP_ADI2 ; 
 scalar_t__ AD5064_REGMAP_LTC ; 
 int ad5064_write (struct ad5064_state*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5064_sync_powerdown_mode(struct ad5064_state *st,
	const struct iio_chan_spec *chan)
{
	unsigned int val, address;
	unsigned int shift;
	int ret;

	if (st->chip_info->regmap_type == AD5064_REGMAP_LTC) {
		val = 0;
		address = chan->address;
	} else {
		if (st->chip_info->regmap_type == AD5064_REGMAP_ADI2)
			shift = 4;
		else
			shift = 8;

		val = (0x1 << chan->address);
		address = 0;

		if (st->pwr_down[chan->channel])
			val |= st->pwr_down_mode[chan->channel] << shift;
	}

	ret = ad5064_write(st, AD5064_CMD_POWERDOWN_DAC, address, val, 0);

	return ret;
}