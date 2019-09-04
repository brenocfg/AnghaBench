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
struct iio_dev {int /*<<< orphan*/  pollfunc_event; int /*<<< orphan*/  modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDIO_EVENT_TRIGGERED ; 
 int /*<<< orphan*/  iio_dealloc_pollfunc (int /*<<< orphan*/ ) ; 

void iio_triggered_event_cleanup(struct iio_dev *indio_dev)
{
	indio_dev->modes &= ~INDIO_EVENT_TRIGGERED;
	iio_dealloc_pollfunc(indio_dev->pollfunc_event);
}