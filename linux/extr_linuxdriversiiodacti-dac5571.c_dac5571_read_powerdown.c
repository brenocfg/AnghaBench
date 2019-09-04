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
struct iio_chan_spec {int dummy; } ;
struct dac5571_data {int powerdown; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct dac5571_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t dac5571_read_powerdown(struct iio_dev *indio_dev,
				      uintptr_t private,
				      const struct iio_chan_spec *chan,
				      char *buf)
{
	struct dac5571_data *data = iio_priv(indio_dev);

	return sprintf(buf, "%d\n", data->powerdown);
}