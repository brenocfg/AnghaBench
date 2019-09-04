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
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int ipa; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int handle_ptff (struct kvm_vcpu*) ; 
 int handle_sckpf (struct kvm_vcpu*) ; 

int kvm_s390_handle_01(struct kvm_vcpu *vcpu)
{
	switch (vcpu->arch.sie_block->ipa & 0x00ff) {
	case 0x04:
		return handle_ptff(vcpu);
	case 0x07:
		return handle_sckpf(vcpu);
	default:
		return -EOPNOTSUPP;
	}
}