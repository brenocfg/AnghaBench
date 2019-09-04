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
struct kvmppc_vcore {int pcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmhv_rm_send_ipi (int) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void kvmhv_interrupt_vcore(struct kvmppc_vcore *vc, int active)
{
	int cpu = vc->pcpu;

	/* Order setting of exit map vs. msgsnd/IPI */
	smp_mb();
	for (; active; active >>= 1, ++cpu)
		if (active & 1)
			kvmhv_rm_send_ipi(cpu);
}