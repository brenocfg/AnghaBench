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
typedef  int /*<<< orphan*/  u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t scan_index; int /*<<< orphan*/  channel; int /*<<< orphan*/  type; } ;
struct adis16260_chip_info {int gyro_max_scale; int gyro_max_val; } ;
struct adis {int /*<<< orphan*/  spi; } ;
struct adis16260 {struct adis adis; struct adis16260_chip_info* info; } ;
typedef  int s16 ;
struct TYPE_2__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16260_ERROR_ACTIVE ; 
 int /*<<< orphan*/  ADIS16260_SMPL_PRD ; 
 int ADIS16260_SMPL_PRD_DIV_MASK ; 
 int ADIS16260_SMPL_PRD_TIME_BASE ; 
 int EINVAL ; 
#define  IIO_ANGL_VEL 137 
#define  IIO_CHAN_INFO_CALIBBIAS 136 
#define  IIO_CHAN_INFO_CALIBSCALE 135 
#define  IIO_CHAN_INFO_OFFSET 134 
#define  IIO_CHAN_INFO_RAW 133 
#define  IIO_CHAN_INFO_SAMP_FREQ 132 
#define  IIO_CHAN_INFO_SCALE 131 
 int IIO_DEGREE_TO_RAD (int) ; 
#define  IIO_INCLI 130 
#define  IIO_TEMP 129 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
#define  IIO_VOLTAGE 128 
 int /*<<< orphan*/ ** adis16260_addresses ; 
 int adis_read_reg_16 (struct adis*,int /*<<< orphan*/ ,int*) ; 
 int adis_single_conversion (struct iio_dev*,struct iio_chan_spec const*,int /*<<< orphan*/ ,int*) ; 
 struct adis16260* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int,int) ; 
 TYPE_1__* spi_get_device_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adis16260_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2,
			      long mask)
{
	struct adis16260 *adis16260 = iio_priv(indio_dev);
	const struct adis16260_chip_info *info = adis16260->info;
	struct adis *adis = &adis16260->adis;
	int ret;
	u8 addr;
	s16 val16;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		return adis_single_conversion(indio_dev, chan,
				ADIS16260_ERROR_ACTIVE, val);
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			*val = info->gyro_max_scale;
			*val2 = info->gyro_max_val;
			return IIO_VAL_FRACTIONAL;
		case IIO_INCLI:
			*val = 0;
			*val2 = IIO_DEGREE_TO_RAD(36630);
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_VOLTAGE:
			if (chan->channel == 0) {
				*val = 1;
				*val2 = 831500; /* 1.8315 mV */
			} else {
				*val = 0;
				*val2 = 610500; /* 610.5 uV */
			}
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val = 145;
			*val2 = 300000; /* 0.1453 C */
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		*val = 250000 / 1453; /* 25 C = 0x00 */
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBBIAS:
		addr = adis16260_addresses[chan->scan_index][0];
		ret = adis_read_reg_16(adis, addr, &val16);
		if (ret)
			return ret;

		*val = sign_extend32(val16, 11);
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_CALIBSCALE:
		addr = adis16260_addresses[chan->scan_index][1];
		ret = adis_read_reg_16(adis, addr, &val16);
		if (ret)
			return ret;

		*val = val16;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = adis_read_reg_16(adis, ADIS16260_SMPL_PRD, &val16);
		if (ret)
			return ret;

		if (spi_get_device_id(adis->spi)->driver_data)
		/* If an adis16251 */
			*val = (val16 & ADIS16260_SMPL_PRD_TIME_BASE) ?
				8 : 256;
		else
			*val = (val16 & ADIS16260_SMPL_PRD_TIME_BASE) ?
				66 : 2048;
		*val /= (val16 & ADIS16260_SMPL_PRD_DIV_MASK) + 1;
		return IIO_VAL_INT;
	}
	return -EINVAL;
}