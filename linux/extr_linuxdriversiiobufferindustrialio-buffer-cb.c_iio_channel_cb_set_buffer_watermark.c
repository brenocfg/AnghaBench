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
struct TYPE_2__ {size_t watermark; } ;
struct iio_cb_buffer {TYPE_1__ buffer; } ;

/* Variables and functions */
 int EINVAL ; 

int iio_channel_cb_set_buffer_watermark(struct iio_cb_buffer *cb_buff,
					size_t watermark)
{
	if (!watermark)
		return -EINVAL;
	cb_buff->buffer.watermark = watermark;

	return 0;
}