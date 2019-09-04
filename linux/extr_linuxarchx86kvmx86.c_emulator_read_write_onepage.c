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
struct x86_exception {int dummy; } ;
struct x86_emulate_ctxt {int dummy; } ;
struct read_write_emulator_ops {int write; int (* read_write_mmio ) (struct kvm_vcpu*,int,unsigned int,void*) ;scalar_t__ (* read_write_emulate ) (struct kvm_vcpu*,int,void*,unsigned int) ;} ;
struct TYPE_2__ {unsigned long gpa_val; scalar_t__ gpa_available; struct x86_emulate_ctxt emulate_ctxt; } ;
struct kvm_vcpu {scalar_t__ mmio_nr_fragments; struct kvm_mmio_fragment* mmio_fragments; TYPE_1__ arch; } ;
struct kvm_mmio_fragment {int gpa; unsigned int len; void* data; } ;
typedef  int gpa_t ;

/* Variables and functions */
 scalar_t__ KVM_MAX_MMIO_FRAGMENTS ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int X86EMUL_CONTINUE ; 
 int X86EMUL_PROPAGATE_FAULT ; 
 scalar_t__ emulator_can_use_gpa (struct x86_emulate_ctxt*) ; 
 scalar_t__ stub1 (struct kvm_vcpu*,int,void*,unsigned int) ; 
 int stub2 (struct kvm_vcpu*,int,unsigned int,void*) ; 
 int vcpu_is_mmio_gpa (struct kvm_vcpu*,unsigned long,int,int) ; 
 int vcpu_mmio_gva_to_gpa (struct kvm_vcpu*,unsigned long,int*,struct x86_exception*,int) ; 

__attribute__((used)) static int emulator_read_write_onepage(unsigned long addr, void *val,
				       unsigned int bytes,
				       struct x86_exception *exception,
				       struct kvm_vcpu *vcpu,
				       const struct read_write_emulator_ops *ops)
{
	gpa_t gpa;
	int handled, ret;
	bool write = ops->write;
	struct kvm_mmio_fragment *frag;
	struct x86_emulate_ctxt *ctxt = &vcpu->arch.emulate_ctxt;

	/*
	 * If the exit was due to a NPF we may already have a GPA.
	 * If the GPA is present, use it to avoid the GVA to GPA table walk.
	 * Note, this cannot be used on string operations since string
	 * operation using rep will only have the initial GPA from the NPF
	 * occurred.
	 */
	if (vcpu->arch.gpa_available &&
	    emulator_can_use_gpa(ctxt) &&
	    (addr & ~PAGE_MASK) == (vcpu->arch.gpa_val & ~PAGE_MASK)) {
		gpa = vcpu->arch.gpa_val;
		ret = vcpu_is_mmio_gpa(vcpu, addr, gpa, write);
	} else {
		ret = vcpu_mmio_gva_to_gpa(vcpu, addr, &gpa, exception, write);
		if (ret < 0)
			return X86EMUL_PROPAGATE_FAULT;
	}

	if (!ret && ops->read_write_emulate(vcpu, gpa, val, bytes))
		return X86EMUL_CONTINUE;

	/*
	 * Is this MMIO handled locally?
	 */
	handled = ops->read_write_mmio(vcpu, gpa, bytes, val);
	if (handled == bytes)
		return X86EMUL_CONTINUE;

	gpa += handled;
	bytes -= handled;
	val += handled;

	WARN_ON(vcpu->mmio_nr_fragments >= KVM_MAX_MMIO_FRAGMENTS);
	frag = &vcpu->mmio_fragments[vcpu->mmio_nr_fragments++];
	frag->gpa = gpa;
	frag->data = val;
	frag->len = bytes;
	return X86EMUL_CONTINUE;
}