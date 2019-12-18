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

/* Variables and functions */
 int /*<<< orphan*/  AD9523_STATUS_SIGNALS ; 
 int AD9523_STATUS_SIGNALS_SYNC_MAN_CTRL ; 
 int ad9523_io_update (struct iio_dev*) ; 
 int ad9523_read (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int ad9523_write (struct iio_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad9523_sync(struct iio_dev *indio_dev)
{
	int ret, tmp;

	ret = ad9523_read(indio_dev, AD9523_STATUS_SIGNALS);
	if (ret < 0)
		return ret;

	tmp = ret;
	tmp |= AD9523_STATUS_SIGNALS_SYNC_MAN_CTRL;

	ret = ad9523_write(indio_dev, AD9523_STATUS_SIGNALS, tmp);
	if (ret < 0)
		return ret;

	ad9523_io_update(indio_dev);
	tmp &= ~AD9523_STATUS_SIGNALS_SYNC_MAN_CTRL;

	ret = ad9523_write(indio_dev, AD9523_STATUS_SIGNALS, tmp);
	if (ret < 0)
		return ret;

	return ad9523_io_update(indio_dev);
}