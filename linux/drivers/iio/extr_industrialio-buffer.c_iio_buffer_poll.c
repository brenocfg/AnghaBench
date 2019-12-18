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
struct poll_table_struct {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  info; struct iio_buffer* buffer; } ;
struct iio_buffer {int /*<<< orphan*/  watermark; int /*<<< orphan*/  pollq; } ;
struct file {struct iio_dev* private_data; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ iio_buffer_ready (struct iio_dev*,struct iio_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__poll_t iio_buffer_poll(struct file *filp,
			     struct poll_table_struct *wait)
{
	struct iio_dev *indio_dev = filp->private_data;
	struct iio_buffer *rb = indio_dev->buffer;

	if (!indio_dev->info || rb == NULL)
		return 0;

	poll_wait(filp, &rb->pollq, wait);
	if (iio_buffer_ready(indio_dev, rb, rb->watermark, 0))
		return EPOLLIN | EPOLLRDNORM;
	return 0;
}