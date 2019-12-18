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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;
struct ad5686_state {int pwr_down_mask; int pwr_down_mode; int (* write ) (struct ad5686_state*,int /*<<< orphan*/ ,int,unsigned int) ;int /*<<< orphan*/  use_internal_vref; TYPE_1__* chip_info; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int regmap_type; } ;

/* Variables and functions */
 unsigned int AD5310_REF_BIT_MSK ; 
#define  AD5310_REGMAP 131 
 unsigned int AD5683_REF_BIT_MSK ; 
#define  AD5683_REGMAP 130 
 int /*<<< orphan*/  AD5686_CMD_POWERDOWN_DAC ; 
#define  AD5686_REGMAP 129 
 unsigned int AD5693_REF_BIT_MSK ; 
#define  AD5693_REGMAP 128 
 int EINVAL ; 
 struct ad5686_state* iio_priv (struct iio_dev*) ; 
 int strtobool (char const*,int*) ; 
 int stub1 (struct ad5686_state*,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static ssize_t ad5686_write_dac_powerdown(struct iio_dev *indio_dev,
					  uintptr_t private,
					  const struct iio_chan_spec *chan,
					  const char *buf,
					  size_t len)
{
	bool readin;
	int ret;
	struct ad5686_state *st = iio_priv(indio_dev);
	unsigned int val, ref_bit_msk;
	u8 shift, address = 0;

	ret = strtobool(buf, &readin);
	if (ret)
		return ret;

	if (readin)
		st->pwr_down_mask |= (0x3 << (chan->channel * 2));
	else
		st->pwr_down_mask &= ~(0x3 << (chan->channel * 2));

	switch (st->chip_info->regmap_type) {
	case AD5310_REGMAP:
		shift = 9;
		ref_bit_msk = AD5310_REF_BIT_MSK;
		break;
	case AD5683_REGMAP:
		shift = 13;
		ref_bit_msk = AD5683_REF_BIT_MSK;
		break;
	case AD5686_REGMAP:
		shift = 0;
		ref_bit_msk = 0;
		/* AD5674R/AD5679R have 16 channels and 2 powerdown registers */
		if (chan->channel > 0x7)
			address = 0x8;
		break;
	case AD5693_REGMAP:
		shift = 13;
		ref_bit_msk = AD5693_REF_BIT_MSK;
		break;
	default:
		return -EINVAL;
	}

	val = ((st->pwr_down_mask & st->pwr_down_mode) << shift);
	if (!st->use_internal_vref)
		val |= ref_bit_msk;

	ret = st->write(st, AD5686_CMD_POWERDOWN_DAC,
			address, val >> (address * 2));

	return ret ? ret : len;
}