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
struct ad5064_state {int* pwr_down_mode; } ;

/* Variables and functions */
 struct ad5064_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad5064_get_powerdown_mode(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan)
{
	struct ad5064_state *st = iio_priv(indio_dev);

	return st->pwr_down_mode[chan->channel] - 1;
}