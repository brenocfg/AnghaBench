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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct ad7150_chip_info {int /*<<< orphan*/  client; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int /*<<< orphan*/  AD7150_CFG ; 
 int /*<<< orphan*/  AD7150_CFG_FIX ; 
 int /*<<< orphan*/  AD7150_THRESHTYPE_MSK ; 
 int EINVAL ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int IIO_EV_DIR_RISING ; 
#define  IIO_EV_TYPE_MAG_ADAPTIVE 130 
#define  IIO_EV_TYPE_THRESH 129 
#define  IIO_EV_TYPE_THRESH_ADAPTIVE 128 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ad7150_chip_info* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7150_read_event_config(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir)
{
	int ret;
	u8 threshtype;
	bool thrfixed;
	struct ad7150_chip_info *chip = iio_priv(indio_dev);

	ret = i2c_smbus_read_byte_data(chip->client, AD7150_CFG);
	if (ret < 0)
		return ret;

	threshtype = FIELD_GET(AD7150_THRESHTYPE_MSK, ret);

	/*check if threshold mode is fixed or adaptive*/
	thrfixed = FIELD_GET(AD7150_CFG_FIX, ret);

	switch (type) {
	case IIO_EV_TYPE_MAG_ADAPTIVE:
		if (dir == IIO_EV_DIR_RISING)
			return !thrfixed && (threshtype == 0x1);
		return !thrfixed && (threshtype == 0x0);
	case IIO_EV_TYPE_THRESH_ADAPTIVE:
		if (dir == IIO_EV_DIR_RISING)
			return !thrfixed && (threshtype == 0x3);
		return !thrfixed && (threshtype == 0x2);
	case IIO_EV_TYPE_THRESH:
		if (dir == IIO_EV_DIR_RISING)
			return thrfixed && (threshtype == 0x1);
		return thrfixed && (threshtype == 0x0);
	default:
		break;
	}
	return -EINVAL;
}