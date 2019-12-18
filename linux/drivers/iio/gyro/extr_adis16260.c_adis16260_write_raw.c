#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {size_t scan_index; } ;
struct adis {TYPE_2__* spi; } ;
struct adis16260 {struct adis adis; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_speed_hz; } ;
struct TYPE_3__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16260_SMPL_PRD ; 
 int ADIS16260_SMPL_PRD_DIV_MASK ; 
 int /*<<< orphan*/  ADIS16260_SPI_FAST ; 
 int /*<<< orphan*/  ADIS16260_SPI_SLOW ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_CALIBSCALE 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int** adis16260_addresses ; 
 int adis_write_reg_16 (struct adis*,int,int) ; 
 int adis_write_reg_8 (struct adis*,int /*<<< orphan*/ ,int) ; 
 struct adis16260* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* spi_get_device_id (TYPE_2__*) ; 

__attribute__((used)) static int adis16260_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	struct adis16260 *adis16260 = iio_priv(indio_dev);
	struct adis *adis = &adis16260->adis;
	int ret;
	u8 addr;
	u8 t;

	switch (mask) {
	case IIO_CHAN_INFO_CALIBBIAS:
		if (val < -2048 || val >= 2048)
			return -EINVAL;

		addr = adis16260_addresses[chan->scan_index][0];
		return adis_write_reg_16(adis, addr, val);
	case IIO_CHAN_INFO_CALIBSCALE:
		if (val < 0 || val >= 4096)
			return -EINVAL;

		addr = adis16260_addresses[chan->scan_index][1];
		return adis_write_reg_16(adis, addr, val);
	case IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&indio_dev->mlock);
		if (spi_get_device_id(adis->spi)->driver_data)
			t = 256 / val;
		else
			t = 2048 / val;

		if (t > ADIS16260_SMPL_PRD_DIV_MASK)
			t = ADIS16260_SMPL_PRD_DIV_MASK;
		else if (t > 0)
			t--;

		if (t >= 0x0A)
			adis->spi->max_speed_hz = ADIS16260_SPI_SLOW;
		else
			adis->spi->max_speed_hz = ADIS16260_SPI_FAST;
		ret = adis_write_reg_8(adis, ADIS16260_SMPL_PRD, t);

		mutex_unlock(&indio_dev->mlock);
		return ret;
	}
	return -EINVAL;
}