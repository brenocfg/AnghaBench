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
struct mcp4725_data {unsigned int powerdown_mode; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 struct mcp4725_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int mcp4725_set_powerdown_mode(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, unsigned mode)
{
	struct mcp4725_data *data = iio_priv(indio_dev);

	data->powerdown_mode = mode;

	return 0;
}