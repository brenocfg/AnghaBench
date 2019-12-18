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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t scan_index; } ;
struct adis {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
#define  IIO_CHAN_INFO_CALIBBIAS 128 
 int /*<<< orphan*/ ** adis16240_addresses ; 
 int adis_write_reg_16 (struct adis*,int /*<<< orphan*/ ,int) ; 
 struct adis* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adis16240_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	struct adis *st = iio_priv(indio_dev);
	u8 addr;

	switch (mask) {
	case IIO_CHAN_INFO_CALIBBIAS:
		addr = adis16240_addresses[chan->scan_index][0];
		return adis_write_reg_16(st, addr, val & GENMASK(9, 0));
	}
	return -EINVAL;
}