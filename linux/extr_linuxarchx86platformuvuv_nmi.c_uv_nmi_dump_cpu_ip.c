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
struct pt_regs {scalar_t__ ip; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void uv_nmi_dump_cpu_ip(int cpu, struct pt_regs *regs)
{
	pr_info("UV: %4d %6d %-32.32s %pS",
		cpu, current->pid, current->comm, (void *)regs->ip);
}