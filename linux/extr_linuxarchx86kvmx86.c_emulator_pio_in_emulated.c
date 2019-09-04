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
struct x86_emulate_ctxt {int dummy; } ;
struct TYPE_3__ {scalar_t__ count; } ;
struct TYPE_4__ {TYPE_1__ pio; int /*<<< orphan*/  pio_data; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PIO_IN ; 
 struct kvm_vcpu* emul_to_vcpu (struct x86_emulate_ctxt*) ; 
 int emulator_pio_in_out (struct kvm_vcpu*,int,unsigned short,void*,unsigned int,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_kvm_pio (int /*<<< orphan*/ ,unsigned short,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emulator_pio_in_emulated(struct x86_emulate_ctxt *ctxt,
				    int size, unsigned short port, void *val,
				    unsigned int count)
{
	struct kvm_vcpu *vcpu = emul_to_vcpu(ctxt);
	int ret;

	if (vcpu->arch.pio.count)
		goto data_avail;

	memset(vcpu->arch.pio_data, 0, size * count);

	ret = emulator_pio_in_out(vcpu, size, port, val, count, true);
	if (ret) {
data_avail:
		memcpy(val, vcpu->arch.pio_data, size * count);
		trace_kvm_pio(KVM_PIO_IN, port, size, count, vcpu->arch.pio_data);
		vcpu->arch.pio.count = 0;
		return 1;
	}

	return 0;
}