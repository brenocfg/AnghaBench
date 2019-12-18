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
#define  XADC_THRESHOLD_OT_MAX 131 
#define  XADC_THRESHOLD_TEMP_MAX 130 
#define  XADC_THRESHOLD_VCCAUX_MAX 129 
#define  XADC_THRESHOLD_VCCINT_MAX 128 

__attribute__((used)) static const struct iio_chan_spec *xadc_event_to_channel(
	struct iio_dev *indio_dev, unsigned int event)
{
	switch (event) {
	case XADC_THRESHOLD_OT_MAX:
	case XADC_THRESHOLD_TEMP_MAX:
		return &indio_dev->channels[0];
	case XADC_THRESHOLD_VCCINT_MAX:
	case XADC_THRESHOLD_VCCAUX_MAX:
		return &indio_dev->channels[event];
	default:
		return &indio_dev->channels[event-1];
	}
}