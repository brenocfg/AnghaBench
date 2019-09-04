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
struct TYPE_3__ {int ipb; } ;

/* Variables and functions */

__attribute__((used)) static inline void kvm_s390_get_regs_rre(struct kvm_vcpu *vcpu, int *r1, int *r2)
{
	if (r1)
		*r1 = (vcpu->arch.sie_block->ipb & 0x00f00000) >> 20;
	if (r2)
		*r2 = (vcpu->arch.sie_block->ipb & 0x000f0000) >> 16;
}