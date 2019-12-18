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
struct iio_chan_spec {size_t channel; } ;
struct ad7150_chip_info {int** mag_sensitivity; int** thresh_sensitivity; int** threshold; int /*<<< orphan*/  state_lock; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_EV_DIR_RISING ; 
#define  IIO_EV_TYPE_MAG_ADAPTIVE 130 
#define  IIO_EV_TYPE_THRESH 129 
#define  IIO_EV_TYPE_THRESH_ADAPTIVE 128 
 int ad7150_write_event_params (struct iio_dev*,size_t,int,int) ; 
 struct ad7150_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7150_write_event_value(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir,
				    enum iio_event_info info,
				    int val, int val2)
{
	int ret;
	struct ad7150_chip_info *chip = iio_priv(indio_dev);
	int rising = (dir == IIO_EV_DIR_RISING);

	mutex_lock(&chip->state_lock);
	switch (type) {
	case IIO_EV_TYPE_MAG_ADAPTIVE:
		chip->mag_sensitivity[rising][chan->channel] = val;
		break;
	case IIO_EV_TYPE_THRESH_ADAPTIVE:
		chip->thresh_sensitivity[rising][chan->channel] = val;
		break;
	case IIO_EV_TYPE_THRESH:
		chip->threshold[rising][chan->channel] = val;
		break;
	default:
		ret = -EINVAL;
		goto error_ret;
	}

	/* write back if active */
	ret = ad7150_write_event_params(indio_dev, chan->channel, type, dir);

error_ret:
	mutex_unlock(&chip->state_lock);
	return ret;
}