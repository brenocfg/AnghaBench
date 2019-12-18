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
struct rescale {TYPE_1__* ext_info; int /*<<< orphan*/  source; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct rescale* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_read_channel_ext_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t rescale_read_ext_info(struct iio_dev *indio_dev,
				     uintptr_t private,
				     struct iio_chan_spec const *chan,
				     char *buf)
{
	struct rescale *rescale = iio_priv(indio_dev);

	return iio_read_channel_ext_info(rescale->source,
					 rescale->ext_info[private].name,
					 buf);
}