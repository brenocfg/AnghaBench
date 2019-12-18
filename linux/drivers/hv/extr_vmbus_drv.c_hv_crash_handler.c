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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCONNECTED ; 
 int /*<<< orphan*/  hv_stimer_cleanup (int) ; 
 int /*<<< orphan*/  hv_synic_cleanup (int) ; 
 int /*<<< orphan*/  hyperv_cleanup () ; 
 int smp_processor_id () ; 
 TYPE_1__ vmbus_connection ; 
 int /*<<< orphan*/  vmbus_initiate_unload (int) ; 

__attribute__((used)) static void hv_crash_handler(struct pt_regs *regs)
{
	int cpu;

	vmbus_initiate_unload(true);
	/*
	 * In crash handler we can't schedule synic cleanup for all CPUs,
	 * doing the cleanup for current CPU only. This should be sufficient
	 * for kdump.
	 */
	vmbus_connection.conn_state = DISCONNECTED;
	cpu = smp_processor_id();
	hv_stimer_cleanup(cpu);
	hv_synic_cleanup(cpu);
	hyperv_cleanup();
}