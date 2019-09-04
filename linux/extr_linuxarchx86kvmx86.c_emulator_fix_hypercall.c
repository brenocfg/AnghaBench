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
struct x86_emulate_ctxt {int /*<<< orphan*/  exception; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* patch_hypercall ) (struct kvm_vcpu*,char*) ;} ;

/* Variables and functions */
 struct kvm_vcpu* emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int emulator_write_emulated (struct x86_emulate_ctxt*,unsigned long,char*,int,int /*<<< orphan*/ *) ; 
 unsigned long kvm_rip_read (struct kvm_vcpu*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,char*) ; 

__attribute__((used)) static int emulator_fix_hypercall(struct x86_emulate_ctxt *ctxt)
{
	struct kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	char instruction[3];
	unsigned long rip = kvm_rip_read(vcpu);

	kvm_x86_ops->patch_hypercall(vcpu, instruction);

	return emulator_write_emulated(ctxt, rip, instruction, 3,
		&ctxt->exception);
}