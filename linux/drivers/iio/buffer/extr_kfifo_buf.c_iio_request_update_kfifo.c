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
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  bytes_per_datum; } ;
struct iio_kfifo {int update_needed; int /*<<< orphan*/  user_lock; int /*<<< orphan*/  kf; TYPE_1__ buffer; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 int __iio_allocate_kfifo (struct iio_kfifo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iio_kfifo* iio_to_kfifo (struct iio_buffer*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_reset_out (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iio_request_update_kfifo(struct iio_buffer *r)
{
	int ret = 0;
	struct iio_kfifo *buf = iio_to_kfifo(r);

	mutex_lock(&buf->user_lock);
	if (buf->update_needed) {
		kfifo_free(&buf->kf);
		ret = __iio_allocate_kfifo(buf, buf->buffer.bytes_per_datum,
				   buf->buffer.length);
		if (ret >= 0)
			buf->update_needed = false;
	} else {
		kfifo_reset_out(&buf->kf);
	}
	mutex_unlock(&buf->user_lock);

	return ret;
}