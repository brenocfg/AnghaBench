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
struct nios2_timer {int /*<<< orphan*/  freq; } ;
struct nios2_clockevent_dev {struct nios2_timer timer; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  nios2_timer_config (struct nios2_timer*,unsigned long,int) ; 
 struct nios2_clockevent_dev* to_nios2_clkevent (struct clock_event_device*) ; 

__attribute__((used)) static int nios2_timer_set_periodic(struct clock_event_device *evt)
{
	unsigned long period;
	struct nios2_clockevent_dev *nios2_ced = to_nios2_clkevent(evt);
	struct nios2_timer *timer = &nios2_ced->timer;

	period = DIV_ROUND_UP(timer->freq, HZ);
	nios2_timer_config(timer, period, true);
	return 0;
}