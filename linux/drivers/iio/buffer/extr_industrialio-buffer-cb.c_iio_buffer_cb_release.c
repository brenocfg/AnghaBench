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
struct TYPE_2__ {int /*<<< orphan*/  scan_mask; } ;
struct iio_cb_buffer {TYPE_1__ buffer; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 struct iio_cb_buffer* buffer_to_cb_buffer (struct iio_buffer*) ; 
 int /*<<< orphan*/  kfree (struct iio_cb_buffer*) ; 

__attribute__((used)) static void iio_buffer_cb_release(struct iio_buffer *buffer)
{
	struct iio_cb_buffer *cb_buff = buffer_to_cb_buffer(buffer);

	bitmap_free(cb_buff->buffer.scan_mask);
	kfree(cb_buff);
}