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
struct iio_trigger {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_trigger_poll_chained (struct iio_trigger*) ; 
 int /*<<< orphan*/  kthread_freezable_should_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  set_freezable () ; 

__attribute__((used)) static int iio_loop_thread(void *data)
{
	struct iio_trigger *trig = data;

	set_freezable();

	do {
		iio_trigger_poll_chained(trig);
	} while (likely(!kthread_freezable_should_stop(NULL)));

	return 0;
}