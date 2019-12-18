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
struct of_phandle_args {scalar_t__* args; } ;
struct iio_dev {int dummy; } ;
struct adc5_chip {int nchannels; TYPE_1__* chan_props; } ;
struct TYPE_2__ {scalar_t__ channel; } ;

/* Variables and functions */
 int EINVAL ; 
 struct adc5_chip* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adc5_of_xlate(struct iio_dev *indio_dev,
				const struct of_phandle_args *iiospec)
{
	struct adc5_chip *adc = iio_priv(indio_dev);
	int i;

	for (i = 0; i < adc->nchannels; i++)
		if (adc->chan_props[i].channel == iiospec->args[0])
			return i;

	return -EINVAL;
}