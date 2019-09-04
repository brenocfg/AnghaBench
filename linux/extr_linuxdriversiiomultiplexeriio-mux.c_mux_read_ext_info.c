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
struct mux {TYPE_1__* ext_info; int /*<<< orphan*/  parent; struct iio_chan_spec const* chan; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_mux_deselect (struct mux*) ; 
 scalar_t__ iio_mux_select (struct mux*,int) ; 
 struct mux* iio_priv (struct iio_dev*) ; 
 scalar_t__ iio_read_channel_ext_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t mux_read_ext_info(struct iio_dev *indio_dev, uintptr_t private,
				 struct iio_chan_spec const *chan, char *buf)
{
	struct mux *mux = iio_priv(indio_dev);
	int idx = chan - mux->chan;
	ssize_t ret;

	ret = iio_mux_select(mux, idx);
	if (ret < 0)
		return ret;

	ret = iio_read_channel_ext_info(mux->parent,
					mux->ext_info[private].name,
					buf);

	iio_mux_deselect(mux);

	return ret;
}