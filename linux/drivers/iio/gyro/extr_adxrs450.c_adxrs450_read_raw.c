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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ADXRS450_DNC1 ; 
 int /*<<< orphan*/  ADXRS450_QUAD1 ; 
 int /*<<< orphan*/  ADXRS450_TEMP1 ; 
 int EINVAL ; 
#define  IIO_ANGL_VEL 133 
#define  IIO_CHAN_INFO_CALIBBIAS 132 
#define  IIO_CHAN_INFO_QUADRATURE_CORRECTION_RAW 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int adxrs450_spi_read_reg_16 (struct iio_dev*,int /*<<< orphan*/ ,int*) ; 
 int adxrs450_spi_sensor_data (struct iio_dev*,int*) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int adxrs450_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val,
			     int *val2,
			     long mask)
{
	int ret;
	s16 t;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			ret = adxrs450_spi_sensor_data(indio_dev, &t);
			if (ret)
				break;
			*val = t;
			ret = IIO_VAL_INT;
			break;
		case IIO_TEMP:
			ret = adxrs450_spi_read_reg_16(indio_dev,
						       ADXRS450_TEMP1, &t);
			if (ret)
				break;
			*val = (t >> 6) + 225;
			ret = IIO_VAL_INT;
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			*val = 0;
			*val2 = 218166;
			return IIO_VAL_INT_PLUS_NANO;
		case IIO_TEMP:
			*val = 200;
			*val2 = 0;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_QUADRATURE_CORRECTION_RAW:
		ret = adxrs450_spi_read_reg_16(indio_dev, ADXRS450_QUAD1, &t);
		if (ret)
			break;
		*val = t;
		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		ret = adxrs450_spi_read_reg_16(indio_dev, ADXRS450_DNC1, &t);
		if (ret)
			break;
		*val = sign_extend32(t, 9);
		ret = IIO_VAL_INT;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}