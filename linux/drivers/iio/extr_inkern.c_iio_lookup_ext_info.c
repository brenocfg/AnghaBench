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
struct iio_channel {TYPE_1__* channel; } ;
struct iio_chan_spec_ext_info {scalar_t__ name; } ;
struct TYPE_2__ {struct iio_chan_spec_ext_info* ext_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static const struct iio_chan_spec_ext_info *iio_lookup_ext_info(
						const struct iio_channel *chan,
						const char *attr)
{
	const struct iio_chan_spec_ext_info *ext_info;

	if (!chan->channel->ext_info)
		return NULL;

	for (ext_info = chan->channel->ext_info; ext_info->name; ++ext_info) {
		if (!strcmp(attr, ext_info->name))
			return ext_info;
	}

	return NULL;
}