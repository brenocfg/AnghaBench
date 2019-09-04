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
struct iio_dev {int dummy; } ;
struct iio_cb_buffer {struct iio_dev* indio_dev; } ;

/* Variables and functions */

struct iio_dev
*iio_channel_cb_get_iio_dev(const struct iio_cb_buffer *cb_buffer)
{
	return cb_buffer->indio_dev;
}