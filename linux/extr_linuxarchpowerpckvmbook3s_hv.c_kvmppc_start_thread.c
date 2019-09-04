#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ptid; struct kvmppc_vcore* kvm_vcore; scalar_t__ fake_suspend; struct kvm_vcpu* kvm_vcpu; } ;
struct paca_struct {TYPE_3__ kvm_hstate; } ;
struct kvmppc_vcore {int pcpu; struct kvm* kvm; } ;
struct TYPE_4__ {int thread_cpu; scalar_t__ ptid; scalar_t__ timer_running; int /*<<< orphan*/  dec_timer; } ;
struct kvm_vcpu {int cpu; TYPE_1__ arch; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpu_in_guest; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_ipi_thread (int) ; 
 struct paca_struct** paca_ptrs ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void kvmppc_start_thread(struct kvm_vcpu *vcpu, struct kvmppc_vcore *vc)
{
	int cpu;
	struct paca_struct *tpaca;
	struct kvm *kvm = vc->kvm;

	cpu = vc->pcpu;
	if (vcpu) {
		if (vcpu->arch.timer_running) {
			hrtimer_try_to_cancel(&vcpu->arch.dec_timer);
			vcpu->arch.timer_running = 0;
		}
		cpu += vcpu->arch.ptid;
		vcpu->cpu = vc->pcpu;
		vcpu->arch.thread_cpu = cpu;
		cpumask_set_cpu(cpu, &kvm->arch.cpu_in_guest);
	}
	tpaca = paca_ptrs[cpu];
	tpaca->kvm_hstate.kvm_vcpu = vcpu;
	tpaca->kvm_hstate.ptid = cpu - vc->pcpu;
	tpaca->kvm_hstate.fake_suspend = 0;
	/* Order stores to hstate.kvm_vcpu etc. before store to kvm_vcore */
	smp_wmb();
	tpaca->kvm_hstate.kvm_vcore = vc;
	if (cpu != smp_processor_id())
		kvmppc_ipi_thread(cpu);
}