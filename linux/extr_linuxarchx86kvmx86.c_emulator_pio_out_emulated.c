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
struct x86_emulate_ctxt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pio_data; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PIO_OUT ; 
 struct kvm_vcpu* emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int emulator_pio_in_out (struct kvm_vcpu*,int,unsigned short,void*,unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  trace_kvm_pio (int /*<<< orphan*/ ,unsigned short,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emulator_pio_out_emulated(struct x86_emulate_ctxt *ctxt,
				     int size, unsigned short port,
				     const void *val, unsigned int count)
{
	struct kvm_vcpu *vcpu = emul_to_vcpu(ctxt);

	memcpy(vcpu->arch.pio_data, val, size * count);
	trace_kvm_pio(KVM_PIO_OUT, port, size, count, vcpu->arch.pio_data);
	return emulator_pio_in_out(vcpu, size, port, (void *)val, count, false);
}