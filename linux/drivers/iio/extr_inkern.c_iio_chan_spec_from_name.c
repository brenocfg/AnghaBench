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
struct iio_dev {int num_channels; struct iio_chan_spec* channels; } ;
struct iio_chan_spec {scalar_t__ datasheet_name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static const struct iio_chan_spec
*iio_chan_spec_from_name(const struct iio_dev *indio_dev, const char *name)
{
	int i;
	const struct iio_chan_spec *chan = NULL;

	for (i = 0; i < indio_dev->num_channels; i++)
		if (indio_dev->channels[i].datasheet_name &&
		    strcmp(name, indio_dev->channels[i].datasheet_name) == 0) {
			chan = &indio_dev->channels[i];
			break;
		}
	return chan;
}