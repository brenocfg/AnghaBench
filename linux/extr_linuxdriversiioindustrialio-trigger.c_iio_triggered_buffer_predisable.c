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
struct iio_dev {int /*<<< orphan*/  pollfunc; int /*<<< orphan*/  trig; } ;

/* Variables and functions */
 int iio_trigger_detach_poll_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iio_triggered_buffer_predisable(struct iio_dev *indio_dev)
{
	return iio_trigger_detach_poll_func(indio_dev->trig,
					     indio_dev->pollfunc);
}