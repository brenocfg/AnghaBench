#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_4__ {scalar_t__ pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  UV_NMI_STATE_DUMP_DONE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  pr_info (char*,char const*,int) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ uv_cpu_nmi ; 
 scalar_t__ uv_nmi_action_is (char*) ; 
 int /*<<< orphan*/  uv_nmi_dump_cpu_ip (int,struct pt_regs*) ; 
 int /*<<< orphan*/  uv_nmi_dump_cpu_ip_hdr () ; 

__attribute__((used)) static void uv_nmi_dump_state_cpu(int cpu, struct pt_regs *regs)
{
	const char *dots = " ................................. ";

	if (cpu == 0)
		uv_nmi_dump_cpu_ip_hdr();

	if (current->pid != 0 || !uv_nmi_action_is("ips"))
		uv_nmi_dump_cpu_ip(cpu, regs);

	if (uv_nmi_action_is("dump")) {
		pr_info("UV:%sNMI process trace for CPU %d\n", dots, cpu);
		show_regs(regs);
	}

	this_cpu_write(uv_cpu_nmi.state, UV_NMI_STATE_DUMP_DONE);
}