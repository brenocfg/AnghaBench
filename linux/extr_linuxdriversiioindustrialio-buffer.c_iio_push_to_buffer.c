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
struct iio_buffer {int /*<<< orphan*/  pollq; TYPE_1__* access; } ;
struct TYPE_2__ {int (* store_to ) (struct iio_buffer*,void const*) ;} ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 void* iio_demux (struct iio_buffer*,void const*) ; 
 int stub1 (struct iio_buffer*,void const*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int iio_push_to_buffer(struct iio_buffer *buffer, const void *data)
{
	const void *dataout = iio_demux(buffer, data);
	int ret;

	ret = buffer->access->store_to(buffer, dataout);
	if (ret)
		return ret;

	/*
	 * We can't just test for watermark to decide if we wake the poll queue
	 * because read may request less samples than the watermark.
	 */
	wake_up_interruptible_poll(&buffer->pollq, EPOLLIN | EPOLLRDNORM);
	return 0;
}