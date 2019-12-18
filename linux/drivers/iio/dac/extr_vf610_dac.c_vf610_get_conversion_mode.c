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
struct vf610_dac {int conv_mode; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 struct vf610_dac* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int vf610_get_conversion_mode(struct iio_dev *indio_dev,
				const struct iio_chan_spec *chan)
{
	struct vf610_dac *info = iio_priv(indio_dev);

	return info->conv_mode;
}