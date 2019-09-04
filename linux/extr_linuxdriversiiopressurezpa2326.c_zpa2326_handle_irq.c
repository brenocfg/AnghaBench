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
struct zpa2326_private {int /*<<< orphan*/  timestamp; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 scalar_t__ iio_priv (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t zpa2326_handle_irq(int irq, void *data)
{
	struct iio_dev *indio_dev = data;

	if (iio_buffer_enabled(indio_dev)) {
		/* Timestamping needed for buffered sampling only. */
		((struct zpa2326_private *)
		 iio_priv(indio_dev))->timestamp = iio_get_time_ns(indio_dev);
	}

	return IRQ_WAKE_THREAD;
}