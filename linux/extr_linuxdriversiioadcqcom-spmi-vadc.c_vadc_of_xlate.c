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
struct vadc_priv {unsigned int nchannels; TYPE_1__* iio_chans; } ;
struct of_phandle_args {scalar_t__* args; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ channel; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vadc_priv* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int vadc_of_xlate(struct iio_dev *indio_dev,
			 const struct of_phandle_args *iiospec)
{
	struct vadc_priv *vadc = iio_priv(indio_dev);
	unsigned int i;

	for (i = 0; i < vadc->nchannels; i++)
		if (vadc->iio_chans[i].channel == iiospec->args[0])
			return i;

	return -EINVAL;
}