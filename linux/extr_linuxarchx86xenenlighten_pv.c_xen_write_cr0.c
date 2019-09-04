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
struct multicall_space {int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MULTI_fpu_taskswitch (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PARAVIRT_LAZY_CPU ; 
 unsigned long X86_CR0_TS ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  xen_cr0_value ; 
 struct multicall_space xen_mc_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_mc_issue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_write_cr0(unsigned long cr0)
{
	struct multicall_space mcs;

	this_cpu_write(xen_cr0_value, cr0);

	/* Only pay attention to cr0.TS; everything else is
	   ignored. */
	mcs = xen_mc_entry(0);

	MULTI_fpu_taskswitch(mcs.mc, (cr0 & X86_CR0_TS) != 0);

	xen_mc_issue(PARAVIRT_LAZY_CPU);
}