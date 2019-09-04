#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_channel {int /*<<< orphan*/  channel; TYPE_2__* indio_dev; } ;
typedef  enum iio_chan_info_enum { ____Placeholder_iio_chan_info_enum } iio_chan_info_enum ;
struct TYPE_4__ {TYPE_1__* info; } ;
struct TYPE_3__ {int (* read_avail ) (TYPE_2__*,int /*<<< orphan*/ ,int const**,int*,int*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  iio_channel_has_available (int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int const**,int*,int*,int) ; 

__attribute__((used)) static int iio_channel_read_avail(struct iio_channel *chan,
				  const int **vals, int *type, int *length,
				  enum iio_chan_info_enum info)
{
	if (!iio_channel_has_available(chan->channel, info))
		return -EINVAL;

	return chan->indio_dev->info->read_avail(chan->indio_dev, chan->channel,
						 vals, type, length, info);
}