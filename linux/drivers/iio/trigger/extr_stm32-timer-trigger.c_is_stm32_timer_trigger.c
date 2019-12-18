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
struct iio_trigger {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  timer_trigger_ops ; 

bool is_stm32_timer_trigger(struct iio_trigger *trig)
{
	return (trig->ops == &timer_trigger_ops);
}