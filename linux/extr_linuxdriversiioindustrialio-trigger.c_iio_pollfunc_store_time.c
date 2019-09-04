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
struct iio_poll_func {int /*<<< orphan*/  indio_dev; int /*<<< orphan*/  timestamp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  iio_get_time_ns (int /*<<< orphan*/ ) ; 

irqreturn_t iio_pollfunc_store_time(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	pf->timestamp = iio_get_time_ns(pf->indio_dev);
	return IRQ_WAKE_THREAD;
}