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
struct kvm_vcpu {TYPE_2__* run; } ;
struct kvm_sync_regs {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  events; int /*<<< orphan*/  sregs; int /*<<< orphan*/  regs; } ;
struct TYPE_4__ {TYPE_3__ regs; } ;
struct TYPE_5__ {int kvm_valid_regs; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int KVM_SYNC_X86_EVENTS ; 
 int KVM_SYNC_X86_REGS ; 
 int KVM_SYNC_X86_SREGS ; 
 int SYNC_REGS_SIZE_BYTES ; 
 int /*<<< orphan*/  __get_regs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __get_sregs (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_vcpu_ioctl_x86_get_vcpu_events (struct kvm_vcpu*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void store_regs(struct kvm_vcpu *vcpu)
{
	BUILD_BUG_ON(sizeof(struct kvm_sync_regs) > SYNC_REGS_SIZE_BYTES);

	if (vcpu->run->kvm_valid_regs & KVM_SYNC_X86_REGS)
		__get_regs(vcpu, &vcpu->run->s.regs.regs);

	if (vcpu->run->kvm_valid_regs & KVM_SYNC_X86_SREGS)
		__get_sregs(vcpu, &vcpu->run->s.regs.sregs);

	if (vcpu->run->kvm_valid_regs & KVM_SYNC_X86_EVENTS)
		kvm_vcpu_ioctl_x86_get_vcpu_events(
				vcpu, &vcpu->run->s.regs.events);
}