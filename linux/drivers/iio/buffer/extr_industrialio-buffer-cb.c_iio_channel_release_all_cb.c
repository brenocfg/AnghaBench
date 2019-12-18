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
struct iio_cb_buffer {int /*<<< orphan*/  buffer; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_buffer_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_channel_release_all (int /*<<< orphan*/ ) ; 

void iio_channel_release_all_cb(struct iio_cb_buffer *cb_buff)
{
	iio_channel_release_all(cb_buff->channels);
	iio_buffer_put(&cb_buff->buffer);
}