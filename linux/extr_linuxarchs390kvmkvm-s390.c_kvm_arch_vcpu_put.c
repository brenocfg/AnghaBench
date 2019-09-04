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
struct TYPE_2__ {int /*<<< orphan*/  enabled_gmap; scalar_t__ cputm_enabled; } ;
struct kvm_vcpu {int cpu; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUSTAT_RUNNING ; 
 int /*<<< orphan*/  __stop_cpu_timer_accounting (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  gmap_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmap_get_enabled () ; 
 int /*<<< orphan*/  is_vcpu_idle (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_clear_cpuflags (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
{
	vcpu->cpu = -1;
	if (vcpu->arch.cputm_enabled && !is_vcpu_idle(vcpu))
		__stop_cpu_timer_accounting(vcpu);
	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_RUNNING);
	vcpu->arch.enabled_gmap = gmap_get_enabled();
	gmap_disable(vcpu->arch.enabled_gmap);

}