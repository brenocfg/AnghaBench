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
struct TYPE_3__ {struct kvm_s390_sie_block* sie_block; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct kvm_s390_sie_block {TYPE_2__ gpsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rewind_psw (TYPE_2__,int) ; 

__attribute__((used)) static inline void kvm_s390_rewind_psw(struct kvm_vcpu *vcpu, int ilen)
{
	struct kvm_s390_sie_block *sie_block = vcpu->arch.sie_block;

	sie_block->gpsw.addr = __rewind_psw(sie_block->gpsw, ilen);
}