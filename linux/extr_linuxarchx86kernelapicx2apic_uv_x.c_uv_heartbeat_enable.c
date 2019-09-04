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
struct timer_list {scalar_t__ expires; } ;
struct TYPE_2__ {int enabled; struct timer_list timer; } ;

/* Variables and functions */
 int SCIR_CPU_ACTIVITY ; 
 scalar_t__ SCIR_CPU_HB_INTERVAL ; 
 int SCIR_CPU_HEARTBEAT ; 
 int /*<<< orphan*/  TIMER_PINNED ; 
 int /*<<< orphan*/  add_timer_on (struct timer_list*,unsigned int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_setup (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* uv_cpu_scir_info (unsigned int) ; 
 int /*<<< orphan*/  uv_heartbeat ; 
 int /*<<< orphan*/  uv_set_cpu_scir_bits (unsigned int,int) ; 

__attribute__((used)) static int uv_heartbeat_enable(unsigned int cpu)
{
	while (!uv_cpu_scir_info(cpu)->enabled) {
		struct timer_list *timer = &uv_cpu_scir_info(cpu)->timer;

		uv_set_cpu_scir_bits(cpu, SCIR_CPU_HEARTBEAT|SCIR_CPU_ACTIVITY);
		timer_setup(timer, uv_heartbeat, TIMER_PINNED);
		timer->expires = jiffies + SCIR_CPU_HB_INTERVAL;
		add_timer_on(timer, cpu);
		uv_cpu_scir_info(cpu)->enabled = 1;

		/* Also ensure that boot CPU is enabled: */
		cpu = 0;
	}
	return 0;
}