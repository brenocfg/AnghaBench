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
typedef  int uint16_t ;
struct xadc {int dummy; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {unsigned char sign; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; int /*<<< orphan*/  type; TYPE_1__ scan_type; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OFFSET 141 
#define  IIO_CHAN_INFO_RAW 140 
#define  IIO_CHAN_INFO_SAMP_FREQ 139 
#define  IIO_CHAN_INFO_SCALE 138 
#define  IIO_TEMP 137 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
#define  IIO_VOLTAGE 136 
 int XADC_CONF2_DIV_MASK ; 
 int XADC_CONF2_DIV_OFFSET ; 
 int /*<<< orphan*/  XADC_REG_CONF2 ; 
#define  XADC_REG_VCCAUX 135 
#define  XADC_REG_VCCBRAM 134 
#define  XADC_REG_VCCINT 133 
#define  XADC_REG_VCCO_DDR 132 
#define  XADC_REG_VCCPAUX 131 
#define  XADC_REG_VCCPINT 130 
#define  XADC_REG_VREFN 129 
#define  XADC_REG_VREFP 128 
 int /*<<< orphan*/  iio_buffer_enabled (struct iio_dev*) ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int,int) ; 
 unsigned int xadc_get_dclk_rate (struct xadc*) ; 
 int xadc_read_adc_reg (struct xadc*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int xadc_read_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int *val, int *val2, long info)
{
	struct xadc *xadc = iio_priv(indio_dev);
	unsigned int div;
	uint16_t val16;
	int ret;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		if (iio_buffer_enabled(indio_dev))
			return -EBUSY;
		ret = xadc_read_adc_reg(xadc, chan->address, &val16);
		if (ret < 0)
			return ret;

		val16 >>= 4;
		if (chan->scan_type.sign == 'u')
			*val = val16;
		else
			*val = sign_extend32(val16, 11);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			/* V = (val * 3.0) / 4096 */
			switch (chan->address) {
			case XADC_REG_VCCINT:
			case XADC_REG_VCCAUX:
			case XADC_REG_VREFP:
			case XADC_REG_VREFN:
			case XADC_REG_VCCBRAM:
			case XADC_REG_VCCPINT:
			case XADC_REG_VCCPAUX:
			case XADC_REG_VCCO_DDR:
				*val = 3000;
				break;
			default:
				*val = 1000;
				break;
			}
			*val2 = 12;
			return IIO_VAL_FRACTIONAL_LOG2;
		case IIO_TEMP:
			/* Temp in C = (val * 503.975) / 4096 - 273.15 */
			*val = 503975;
			*val2 = 12;
			return IIO_VAL_FRACTIONAL_LOG2;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		/* Only the temperature channel has an offset */
		*val = -((273150 << 12) / 503975);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = xadc_read_adc_reg(xadc, XADC_REG_CONF2, &val16);
		if (ret)
			return ret;

		div = (val16 & XADC_CONF2_DIV_MASK) >> XADC_CONF2_DIV_OFFSET;
		if (div < 2)
			div = 2;

		*val = xadc_get_dclk_rate(xadc) / div / 26;

		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}