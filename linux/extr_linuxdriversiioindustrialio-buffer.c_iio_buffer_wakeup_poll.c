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
struct iio_dev {TYPE_1__* buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  pollq; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iio_buffer_wakeup_poll(struct iio_dev *indio_dev)
{
	if (!indio_dev->buffer)
		return;

	wake_up(&indio_dev->buffer->pollq);
}