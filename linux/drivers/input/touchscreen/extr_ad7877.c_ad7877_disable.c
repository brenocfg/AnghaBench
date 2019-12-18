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
struct ad7877 {int disabled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  timer; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad7877_ts_event_release (struct ad7877*) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ad7877_disable(void *data)
{
	struct ad7877 *ts = data;

	mutex_lock(&ts->mutex);

	if (!ts->disabled) {
		ts->disabled = true;
		disable_irq(ts->spi->irq);

		if (del_timer_sync(&ts->timer))
			ad7877_ts_event_release(ts);
	}

	/*
	 * We know the chip's in lowpower mode since we always
	 * leave it that way after every request
	 */

	mutex_unlock(&ts->mutex);
}