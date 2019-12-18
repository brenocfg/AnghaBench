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
struct iio_channel {int /*<<< orphan*/  channel; int /*<<< orphan*/  indio_dev; } ;
struct iio_chan_spec_ext_info {int /*<<< orphan*/  private; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t) ;} ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct iio_chan_spec_ext_info* iio_lookup_ext_info (struct iio_channel*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t) ; 

ssize_t iio_write_channel_ext_info(struct iio_channel *chan, const char *attr,
				   const char *buf, size_t len)
{
	const struct iio_chan_spec_ext_info *ext_info;

	ext_info = iio_lookup_ext_info(chan, attr);
	if (!ext_info)
		return -EINVAL;

	return ext_info->write(chan->indio_dev, ext_info->private,
			       chan->channel, buf, len);
}