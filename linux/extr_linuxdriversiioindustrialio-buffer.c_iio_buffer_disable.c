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
struct iio_dev {int dummy; } ;
struct iio_buffer {TYPE_1__* access; } ;
struct TYPE_2__ {int (* disable ) (struct iio_buffer*,struct iio_dev*) ;} ;

/* Variables and functions */
 int stub1 (struct iio_buffer*,struct iio_dev*) ; 

__attribute__((used)) static int iio_buffer_disable(struct iio_buffer *buffer,
	struct iio_dev *indio_dev)
{
	if (!buffer->access->disable)
		return 0;
	return buffer->access->disable(buffer, indio_dev);
}