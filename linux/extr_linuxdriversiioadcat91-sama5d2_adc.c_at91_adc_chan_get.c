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
struct iio_dev {struct iio_chan_spec const* channels; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int at91_adc_chan_xlate (struct iio_dev*,int) ; 

__attribute__((used)) static inline struct iio_chan_spec const *
at91_adc_chan_get(struct iio_dev *indio_dev, int chan)
{
	int index = at91_adc_chan_xlate(indio_dev, chan);

	if (index < 0)
		return NULL;
	return indio_dev->channels + index;
}