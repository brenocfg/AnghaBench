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
struct x86_emulate_ctxt {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int X86EMUL_CONTINUE ; 
 int X86EMUL_IO_NEEDED ; 
 struct kvm_vcpu* emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int kvm_vcpu_read_guest (struct kvm_vcpu*,unsigned long,void*,unsigned int) ; 

__attribute__((used)) static int kvm_read_guest_phys_system(struct x86_emulate_ctxt *ctxt,
		unsigned long addr, void *val, unsigned int bytes)
{
	struct kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	int r = kvm_vcpu_read_guest(vcpu, addr, val, bytes);

	return r < 0 ? X86EMUL_IO_NEEDED : X86EMUL_CONTINUE;
}