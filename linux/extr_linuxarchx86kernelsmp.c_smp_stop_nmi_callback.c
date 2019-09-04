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
 int NMI_HANDLED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_emergency_vmxoff () ; 
 scalar_t__ raw_smp_processor_id () ; 
 int /*<<< orphan*/  stop_this_cpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stopping_cpu ; 

__attribute__((used)) static int smp_stop_nmi_callback(unsigned int val, struct pt_regs *regs)
{
	/* We are registered on stopping cpu too, avoid spurious NMI */
	if (raw_smp_processor_id() == atomic_read(&stopping_cpu))
		return NMI_HANDLED;

	cpu_emergency_vmxoff();
	stop_this_cpu(NULL);

	return NMI_HANDLED;
}