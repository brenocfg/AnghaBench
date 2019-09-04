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
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RESCHEDULE_VECTOR ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  cpu_is_offline (int) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void native_smp_send_reschedule(int cpu)
{
	if (unlikely(cpu_is_offline(cpu))) {
		WARN(1, "sched: Unexpected reschedule of offline CPU#%d!\n", cpu);
		return;
	}
	apic->send_IPI(cpu, RESCHEDULE_VECTOR);
}