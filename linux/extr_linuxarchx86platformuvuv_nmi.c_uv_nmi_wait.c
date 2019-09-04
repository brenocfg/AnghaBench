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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  UV_NMI_STATE_IN ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_pr_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_weight (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ uv_cpu_nmi ; 
 int /*<<< orphan*/  uv_nmi_cpu_mask ; 
 int /*<<< orphan*/  uv_nmi_cpus_in_nmi ; 
 int /*<<< orphan*/  uv_nmi_nr_cpus_ping () ; 
 int /*<<< orphan*/  uv_nmi_wait_cpus (int) ; 

__attribute__((used)) static void uv_nmi_wait(int master)
{
	/* Indicate this CPU is in: */
	this_cpu_write(uv_cpu_nmi.state, UV_NMI_STATE_IN);

	/* If not the first CPU in (the master), then we are a slave CPU */
	if (!master)
		return;

	do {
		/* Wait for all other CPU's to gather here */
		if (!uv_nmi_wait_cpus(1))
			break;

		/* If not all made it in, send IPI NMI to them */
		pr_alert("UV: Sending NMI IPI to %d CPUs: %*pbl\n",
			 cpumask_weight(uv_nmi_cpu_mask),
			 cpumask_pr_args(uv_nmi_cpu_mask));

		uv_nmi_nr_cpus_ping();

		/* If all CPU's are in, then done */
		if (!uv_nmi_wait_cpus(0))
			break;

		pr_alert("UV: %d CPUs not in NMI loop: %*pbl\n",
			 cpumask_weight(uv_nmi_cpu_mask),
			 cpumask_pr_args(uv_nmi_cpu_mask));
	} while (0);

	pr_alert("UV: %d of %d CPUs in NMI\n",
		atomic_read(&uv_nmi_cpus_in_nmi), num_online_cpus());
}