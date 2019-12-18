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
struct ltc2952_poweroff {int /*<<< orphan*/  wde_interval; int /*<<< orphan*/  gpio_watchdog; scalar_t__ kernel_panic; } ;
struct hrtimer {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;

/* Variables and functions */
 int HRTIMER_NORESTART ; 
 int HRTIMER_RESTART ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hrtimer_cb_get_time (struct hrtimer*) ; 
 unsigned long hrtimer_forward (struct hrtimer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_wde ; 
 struct ltc2952_poweroff* to_ltc2952 (struct hrtimer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum hrtimer_restart ltc2952_poweroff_timer_wde(struct hrtimer *timer)
{
	ktime_t now;
	int state;
	unsigned long overruns;
	struct ltc2952_poweroff *data = to_ltc2952(timer, timer_wde);

	if (data->kernel_panic)
		return HRTIMER_NORESTART;

	state = gpiod_get_value(data->gpio_watchdog);
	gpiod_set_value(data->gpio_watchdog, !state);

	now = hrtimer_cb_get_time(timer);
	overruns = hrtimer_forward(timer, now, data->wde_interval);

	return HRTIMER_RESTART;
}