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

unsigned int iio_get_channel_ext_info_count(struct iio_channel *chan)
{
	const struct iio_chan_spec_ext_info *ext_info;
	unsigned int i = 0;

	if (!chan->channel->ext_info)
		return i;

	for (ext_info = chan->channel->ext_info; ext_info->name; ext_info++)
		++i;

	return i;
}