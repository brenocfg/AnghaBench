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
typedef  int u32 ;
struct x86_exception {int dummy; } ;
struct x86_emulate_ctxt {int dummy; } ;
struct TYPE_5__ {TYPE_1__* walk_mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int gva_t ;
typedef  int gpa_t ;
struct TYPE_6__ {int (* get_cpl ) (struct kvm_vcpu*) ;} ;
struct TYPE_4__ {int (* gva_to_gpa ) (struct kvm_vcpu*,int,int,struct x86_exception*) ;} ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PFERR_FETCH_MASK ; 
 int PFERR_USER_MASK ; 
 int UNMAPPED_GVA ; 
 scalar_t__ WARN_ON (int) ; 
 int X86EMUL_CONTINUE ; 
 int X86EMUL_IO_NEEDED ; 
 int X86EMUL_PROPAGATE_FAULT ; 
 struct kvm_vcpu* emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int kvm_vcpu_read_guest_page (struct kvm_vcpu*,int,void*,unsigned int,unsigned int) ; 
 TYPE_3__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*) ; 
 int stub2 (struct kvm_vcpu*,int,int,struct x86_exception*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int kvm_fetch_guest_virt(struct x86_emulate_ctxt *ctxt,
				gva_t addr, void *val, unsigned int bytes,
				struct x86_exception *exception)
{
	struct kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	u32 access = (kvm_x86_ops->get_cpl(vcpu) == 3) ? PFERR_USER_MASK : 0;
	unsigned offset;
	int ret;

	/* Inline kvm_read_guest_virt_helper for speed.  */
	gpa_t gpa = vcpu->arch.walk_mmu->gva_to_gpa(vcpu, addr, access|PFERR_FETCH_MASK,
						    exception);
	if (unlikely(gpa == UNMAPPED_GVA))
		return X86EMUL_PROPAGATE_FAULT;

	offset = addr & (PAGE_SIZE-1);
	if (WARN_ON(offset + bytes > PAGE_SIZE))
		bytes = (unsigned)PAGE_SIZE - offset;
	ret = kvm_vcpu_read_guest_page(vcpu, gpa >> PAGE_SHIFT, val,
				       offset, bytes);
	if (unlikely(ret < 0))
		return X86EMUL_IO_NEEDED;

	return X86EMUL_CONTINUE;
}