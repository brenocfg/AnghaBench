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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLAVE_EXIT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  pr_alert (char*,int) ; 
 int /*<<< orphan*/  uv_nmi_cpus_in_nmi ; 
 int /*<<< orphan*/  uv_nmi_slave_continue ; 
 int /*<<< orphan*/  uv_nmi_sync_exit (int) ; 

__attribute__((used)) static void uv_nmi_action_health(int cpu, struct pt_regs *regs, int master)
{
	if (master) {
		int in = atomic_read(&uv_nmi_cpus_in_nmi);
		int out = num_online_cpus() - in;

		pr_alert("UV: NMI CPU health check (non-responding:%d)\n", out);
		atomic_set(&uv_nmi_slave_continue, SLAVE_EXIT);
	} else {
		while (!atomic_read(&uv_nmi_slave_continue))
			cpu_relax();
	}
	uv_nmi_sync_exit(master);
}