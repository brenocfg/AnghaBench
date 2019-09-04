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
struct iio_trigger {TYPE_1__* ops; int /*<<< orphan*/  use_count; } ;
struct TYPE_2__ {scalar_t__ (* try_reenable ) (struct iio_trigger*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_trigger_poll (struct iio_trigger*) ; 
 scalar_t__ stub1 (struct iio_trigger*) ; 

void iio_trigger_notify_done(struct iio_trigger *trig)
{
	if (atomic_dec_and_test(&trig->use_count) && trig->ops &&
	    trig->ops->try_reenable)
		if (trig->ops->try_reenable(trig))
			/* Missed an interrupt so launch new poll now */
			iio_trigger_poll(trig);
}