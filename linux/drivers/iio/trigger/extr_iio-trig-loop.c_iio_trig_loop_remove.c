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
struct iio_loop_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_trigger_free (int /*<<< orphan*/ ) ; 
 struct iio_loop_info* iio_trigger_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iio_loop_info*) ; 

__attribute__((used)) static int iio_trig_loop_remove(struct iio_sw_trigger *swt)
{
	struct iio_loop_info *trig_info;

	trig_info = iio_trigger_get_drvdata(swt->trigger);

	iio_trigger_unregister(swt->trigger);
	iio_trigger_free(swt->trigger);
	kfree(trig_info);

	return 0;
}