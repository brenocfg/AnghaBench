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
struct ltc2952_poweroff {int /*<<< orphan*/  dev; } ;
struct hrtimer {int dummy; } ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;

/* Variables and functions */
 int HRTIMER_NORESTART ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ltc2952_poweroff_start_wde (struct ltc2952_poweroff*) ; 
 int /*<<< orphan*/  orderly_poweroff (int) ; 
 int /*<<< orphan*/  timer_trigger ; 
 struct ltc2952_poweroff* to_ltc2952 (struct hrtimer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum hrtimer_restart
ltc2952_poweroff_timer_trigger(struct hrtimer *timer)
{
	struct ltc2952_poweroff *data = to_ltc2952(timer, timer_trigger);

	ltc2952_poweroff_start_wde(data);
	dev_info(data->dev, "executing shutdown\n");
	orderly_poweroff(true);

	return HRTIMER_NORESTART;
}