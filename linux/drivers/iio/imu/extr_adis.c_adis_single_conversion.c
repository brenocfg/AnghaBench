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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct TYPE_2__ {int storagebits; char sign; int realbits; } ;
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  address; } ;
struct adis {int dummy; } ;

/* Variables and functions */
 int IIO_VAL_INT ; 
 int adis_check_status (struct adis*) ; 
 int adis_read_reg (struct adis*,int /*<<< orphan*/ ,unsigned int*,int) ; 
 struct adis* iio_device_get_drvdata (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (unsigned int,int) ; 

int adis_single_conversion(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, unsigned int error_mask, int *val)
{
	struct adis *adis = iio_device_get_drvdata(indio_dev);
	unsigned int uval;
	int ret;

	mutex_lock(&indio_dev->mlock);

	ret = adis_read_reg(adis, chan->address, &uval,
			chan->scan_type.storagebits / 8);
	if (ret)
		goto err_unlock;

	if (uval & error_mask) {
		ret = adis_check_status(adis);
		if (ret)
			goto err_unlock;
	}

	if (chan->scan_type.sign == 's')
		*val = sign_extend32(uval, chan->scan_type.realbits - 1);
	else
		*val = uval & ((1 << chan->scan_type.realbits) - 1);

	ret = IIO_VAL_INT;
err_unlock:
	mutex_unlock(&indio_dev->mlock);
	return ret;
}