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
struct iio_sw_trigger {int /*<<< orphan*/  trigger; } ;
struct iio_hrtimer_info {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_trigger_free (int /*<<< orphan*/ ) ; 
 struct iio_hrtimer_info* iio_trigger_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iio_hrtimer_info*) ; 

__attribute__((used)) static int iio_trig_hrtimer_remove(struct iio_sw_trigger *swt)
{
	struct iio_hrtimer_info *trig_info;

	trig_info = iio_trigger_get_drvdata(swt->trigger);

	iio_trigger_unregister(swt->trigger);

	/* cancel the timer after unreg to make sure no one rearms it */
	hrtimer_cancel(&trig_info->timer);
	iio_trigger_free(swt->trigger);
	kfree(trig_info);

	return 0;
}