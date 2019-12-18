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
struct TYPE_3__ {int (* write_raw ) (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int iio_channel_write(struct iio_channel *chan, int val, int val2,
			     enum iio_chan_info_enum info)
{
	return chan->indio_dev->info->write_raw(chan->indio_dev,
						chan->channel, val, val2, info);
}