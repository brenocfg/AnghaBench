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
struct mvpp2_port_pcpu {int timer_scheduled; int /*<<< orphan*/  tx_done_timer; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int /*<<< orphan*/  MVPP2_TXDONE_HRTIMER_PERIOD_NS ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_timer_set(struct mvpp2_port_pcpu *port_pcpu)
{
	ktime_t interval;

	if (!port_pcpu->timer_scheduled) {
		port_pcpu->timer_scheduled = true;
		interval = MVPP2_TXDONE_HRTIMER_PERIOD_NS;
		hrtimer_start(&port_pcpu->tx_done_timer, interval,
			      HRTIMER_MODE_REL_PINNED);
	}
}