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
struct max5821_data {int* powerdown; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct max5821_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t max5821_read_dac_powerdown(struct iio_dev *indio_dev,
					  uintptr_t private,
					  const struct iio_chan_spec *chan,
					  char *buf)
{
	struct max5821_data *st = iio_priv(indio_dev);

	return sprintf(buf, "%d\n", st->powerdown[chan->channel]);
}