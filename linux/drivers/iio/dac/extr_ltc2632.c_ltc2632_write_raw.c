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
struct ltc2632_state {int /*<<< orphan*/  spi_dev; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int realbits; int /*<<< orphan*/  shift; } ;
struct iio_chan_spec {TYPE_1__ scan_type; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int /*<<< orphan*/  LTC2632_CMD_WRITE_INPUT_N_UPDATE_N ; 
 struct ltc2632_state* iio_priv (struct iio_dev*) ; 
 int ltc2632_spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc2632_write_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int val,
			     int val2,
			     long mask)
{
	struct ltc2632_state *st = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (val >= (1 << chan->scan_type.realbits) || val < 0)
			return -EINVAL;

		return ltc2632_spi_write(st->spi_dev,
					 LTC2632_CMD_WRITE_INPUT_N_UPDATE_N,
					 chan->address, val,
					 chan->scan_type.shift);
	default:
		return -EINVAL;
	}
}