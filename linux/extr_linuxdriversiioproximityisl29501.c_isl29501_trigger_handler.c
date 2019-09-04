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
typedef  int /*<<< orphan*/  u32 ;
struct isl29501_private {int dummy; } ;
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {unsigned long* active_scan_mask; int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ISL29501_DISTANCE_SCAN_INDEX ; 
 int /*<<< orphan*/  REG_DISTANCE ; 
 struct isl29501_private* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isl29501_register_read (struct isl29501_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long const*) ; 

__attribute__((used)) static irqreturn_t isl29501_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct isl29501_private *isl29501 = iio_priv(indio_dev);
	const unsigned long *active_mask = indio_dev->active_scan_mask;
	u32 buffer[4] = {}; /* 1x16-bit + ts */

	if (test_bit(ISL29501_DISTANCE_SCAN_INDEX, active_mask))
		isl29501_register_read(isl29501, REG_DISTANCE, buffer);

	iio_push_to_buffers_with_timestamp(indio_dev, buffer, pf->timestamp);
	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}