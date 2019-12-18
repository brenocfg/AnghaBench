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
struct iio_chan_spec {int type; size_t scan_index; } ;
struct adis {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
#define  IIO_ACCEL 129 
 long IIO_CHAN_INFO_CALIBBIAS ; 
#define  IIO_INCLI 128 
 int /*<<< orphan*/ ** adis16209_addresses ; 
 int adis_write_reg_16 (struct adis*,int /*<<< orphan*/ ,int) ; 
 struct adis* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16209_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	struct adis *st = iio_priv(indio_dev);
	int m;

	if (mask != IIO_CHAN_INFO_CALIBBIAS)
		return -EINVAL;

	switch (chan->type) {
	case IIO_ACCEL:
	case IIO_INCLI:
		m = GENMASK(13, 0);
		break;
	default:
		return -EINVAL;
	}

	return adis_write_reg_16(st, adis16209_addresses[chan->scan_index][0],
				 val & m);
}