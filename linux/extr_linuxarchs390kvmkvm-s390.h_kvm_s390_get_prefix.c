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
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int prefix; } ;

/* Variables and functions */
 int GUEST_PREFIX_SHIFT ; 

__attribute__((used)) static inline u32 kvm_s390_get_prefix(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.sie_block->prefix << GUEST_PREFIX_SHIFT;
}