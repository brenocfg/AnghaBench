#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_7__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_5__* run; TYPE_2__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/ * gprs; } ;
struct TYPE_9__ {TYPE_3__ regs; } ;
struct TYPE_10__ {TYPE_4__ s; } ;
struct TYPE_6__ {int ipb; } ;

/* Variables and functions */

__attribute__((used)) static inline void kvm_s390_get_base_disp_sse(struct kvm_vcpu *vcpu,
					      u64 *address1, u64 *address2,
					      u8 *ar_b1, u8 *ar_b2)
{
	u32 base1 = (vcpu->arch.sie_block->ipb & 0xf0000000) >> 28;
	u32 disp1 = (vcpu->arch.sie_block->ipb & 0x0fff0000) >> 16;
	u32 base2 = (vcpu->arch.sie_block->ipb & 0xf000) >> 12;
	u32 disp2 = vcpu->arch.sie_block->ipb & 0x0fff;

	*address1 = (base1 ? vcpu->run->s.regs.gprs[base1] : 0) + disp1;
	*address2 = (base2 ? vcpu->run->s.regs.gprs[base2] : 0) + disp2;

	if (ar_b1)
		*ar_b1 = base1;
	if (ar_b2)
		*ar_b2 = base2;
}