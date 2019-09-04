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
struct uv_hub_nmi_s {int dummy; } ;
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  pinging; } ;

/* Variables and functions */
 int NMI_DONE ; 
 int NMI_HANDLED ; 
 int SLAVE_CLEAR ; 
 int /*<<< orphan*/  UV_NMI_STATE_OUT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ cpumask_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_call_kgdb_kdb (int,struct pt_regs*,int) ; 
 int /*<<< orphan*/  uv_check_nmi (struct uv_hub_nmi_s*) ; 
 int /*<<< orphan*/  uv_clear_nmi (int) ; 
 TYPE_1__ uv_cpu_nmi ; 
 struct uv_hub_nmi_s* uv_hub_nmi ; 
 int /*<<< orphan*/  uv_in_nmi ; 
 int /*<<< orphan*/  uv_nmi_action ; 
 int /*<<< orphan*/  uv_nmi_action_health (int,struct pt_regs*,int) ; 
 scalar_t__ uv_nmi_action_is (char*) ; 
 int /*<<< orphan*/  uv_nmi_cleanup_mask () ; 
 int /*<<< orphan*/  uv_nmi_cpu ; 
 int /*<<< orphan*/  uv_nmi_cpu_mask ; 
 int /*<<< orphan*/  uv_nmi_cpus_in_nmi ; 
 int /*<<< orphan*/  uv_nmi_dump_state (int,struct pt_regs*,int) ; 
 int /*<<< orphan*/  uv_nmi_kdump (int,int,struct pt_regs*) ; 
 int /*<<< orphan*/  uv_nmi_kexec_failed ; 
 int /*<<< orphan*/  uv_nmi_slave_continue ; 
 int /*<<< orphan*/  uv_nmi_sync_exit (int) ; 
 int /*<<< orphan*/  uv_nmi_touch_watchdogs () ; 
 int /*<<< orphan*/  uv_nmi_wait (int) ; 

__attribute__((used)) static int uv_handle_nmi(unsigned int reason, struct pt_regs *regs)
{
	struct uv_hub_nmi_s *hub_nmi = uv_hub_nmi;
	int cpu = smp_processor_id();
	int master = 0;
	unsigned long flags;

	local_irq_save(flags);

	/* If not a UV System NMI, ignore */
	if (!this_cpu_read(uv_cpu_nmi.pinging) && !uv_check_nmi(hub_nmi)) {
		local_irq_restore(flags);
		return NMI_DONE;
	}

	/* Indicate we are the first CPU into the NMI handler */
	master = (atomic_read(&uv_nmi_cpu) == cpu);

	/* If NMI action is "kdump", then attempt to do it */
	if (uv_nmi_action_is("kdump")) {
		uv_nmi_kdump(cpu, master, regs);

		/* Unexpected return, revert action to "dump" */
		if (master)
			strncpy(uv_nmi_action, "dump", strlen(uv_nmi_action));
	}

	/* Pause as all CPU's enter the NMI handler */
	uv_nmi_wait(master);

	/* Process actions other than "kdump": */
	if (uv_nmi_action_is("health")) {
		uv_nmi_action_health(cpu, regs, master);
	} else if (uv_nmi_action_is("ips") || uv_nmi_action_is("dump")) {
		uv_nmi_dump_state(cpu, regs, master);
	} else if (uv_nmi_action_is("kdb") || uv_nmi_action_is("kgdb")) {
		uv_call_kgdb_kdb(cpu, regs, master);
	} else {
		if (master)
			pr_alert("UV: unknown NMI action: %s\n", uv_nmi_action);
		uv_nmi_sync_exit(master);
	}

	/* Clear per_cpu "in_nmi" flag */
	this_cpu_write(uv_cpu_nmi.state, UV_NMI_STATE_OUT);

	/* Clear MMR NMI flag on each hub */
	uv_clear_nmi(cpu);

	/* Clear global flags */
	if (master) {
		if (cpumask_weight(uv_nmi_cpu_mask))
			uv_nmi_cleanup_mask();
		atomic_set(&uv_nmi_cpus_in_nmi, -1);
		atomic_set(&uv_nmi_cpu, -1);
		atomic_set(&uv_in_nmi, 0);
		atomic_set(&uv_nmi_kexec_failed, 0);
		atomic_set(&uv_nmi_slave_continue, SLAVE_CLEAR);
	}

	uv_nmi_touch_watchdogs();
	local_irq_restore(flags);

	return NMI_HANDLED;
}