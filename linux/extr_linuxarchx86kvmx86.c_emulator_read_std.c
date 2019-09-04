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
typedef  int /*<<< orphan*/  u32 ;
struct x86_exception {int dummy; } ;
struct x86_emulate_ctxt {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_2__ {int (* get_cpl ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PFERR_USER_MASK ; 
 struct kvm_vcpu* emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int kvm_read_guest_virt_helper (int /*<<< orphan*/ ,void*,unsigned int,struct kvm_vcpu*,int /*<<< orphan*/ ,struct x86_exception*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static int emulator_read_std(struct x86_emulate_ctxt *ctxt,
			     gva_t addr, void *val, unsigned int bytes,
			     struct x86_exception *exception, bool system)
{
	struct kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	u32 access = 0;

	if (!system && kvm_x86_ops->get_cpl(vcpu) == 3)
		access |= PFERR_USER_MASK;

	return kvm_read_guest_virt_helper(addr, val, bytes, vcpu, access, exception);
}