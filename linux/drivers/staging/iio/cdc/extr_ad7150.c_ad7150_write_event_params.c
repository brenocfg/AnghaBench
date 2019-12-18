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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct iio_dev {int dummy; } ;
struct ad7150_chip_info {scalar_t__ current_event; int /*<<< orphan*/  client; int /*<<< orphan*/ ** thresh_timeout; int /*<<< orphan*/ ** thresh_sensitivity; int /*<<< orphan*/ ** mag_timeout; int /*<<< orphan*/ ** mag_sensitivity; int /*<<< orphan*/ ** threshold; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IIO_CAPACITANCE ; 
 int IIO_EV_DIR_RISING ; 
#define  IIO_EV_TYPE_MAG_ADAPTIVE 130 
#define  IIO_EV_TYPE_THRESH 129 
#define  IIO_EV_TYPE_THRESH_ADAPTIVE 128 
 scalar_t__ IIO_UNMOD_EVENT_CODE (int /*<<< orphan*/ ,unsigned int,int,int) ; 
 int /*<<< orphan*/ ** ad7150_addresses ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ad7150_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  swab16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7150_write_event_params(struct iio_dev *indio_dev,
				     unsigned int chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir)
{
	int ret;
	u16 value;
	u8 sens, timeout;
	struct ad7150_chip_info *chip = iio_priv(indio_dev);
	int rising = (dir == IIO_EV_DIR_RISING);
	u64 event_code;

	event_code = IIO_UNMOD_EVENT_CODE(IIO_CAPACITANCE, chan, type, dir);

	if (event_code != chip->current_event)
		return 0;

	switch (type) {
		/* Note completely different from the adaptive versions */
	case IIO_EV_TYPE_THRESH:
		value = chip->threshold[rising][chan];
		return i2c_smbus_write_word_data(chip->client,
						 ad7150_addresses[chan][3],
						 swab16(value));
	case IIO_EV_TYPE_MAG_ADAPTIVE:
		sens = chip->mag_sensitivity[rising][chan];
		timeout = chip->mag_timeout[rising][chan];
		break;
	case IIO_EV_TYPE_THRESH_ADAPTIVE:
		sens = chip->thresh_sensitivity[rising][chan];
		timeout = chip->thresh_timeout[rising][chan];
		break;
	default:
		return -EINVAL;
	}
	ret = i2c_smbus_write_byte_data(chip->client,
					ad7150_addresses[chan][4],
					sens);
	if (ret)
		return ret;
	return i2c_smbus_write_byte_data(chip->client,
					ad7150_addresses[chan][5],
					timeout);
}