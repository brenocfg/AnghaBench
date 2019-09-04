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
struct TYPE_4__ {int /*<<< orphan*/  ldt; } ;
struct vcpu_svm {int /*<<< orphan*/ * host_user_msrs; TYPE_2__ host; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_state_reload; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;

/* Variables and functions */
 int NR_HOST_SAVE_USER_MSRS ; 
 int /*<<< orphan*/  avic_vcpu_put (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * host_save_user_msrs ; 
 int /*<<< orphan*/  kvm_load_ldt (int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svm_vcpu_put(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	int i;

	avic_vcpu_put(vcpu);

	++vcpu->stat.host_state_reload;
	kvm_load_ldt(svm->host.ldt);
#ifdef CONFIG_X86_64
	loadsegment(fs, svm->host.fs);
	wrmsrl(MSR_KERNEL_GS_BASE, current->thread.gsbase);
	load_gs_index(svm->host.gs);
#else
#ifdef CONFIG_X86_32_LAZY_GS
	loadsegment(gs, svm->host.gs);
#endif
#endif
	for (i = 0; i < NR_HOST_SAVE_USER_MSRS; i++)
		wrmsrl(host_save_user_msrs[i], svm->host_user_msrs[i]);
}