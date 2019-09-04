#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_vcpu {TYPE_3__* kvm; int /*<<< orphan*/  vcpu_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  idle_mask; } ;
struct TYPE_5__ {TYPE_1__ float_int; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int is_vcpu_idle(struct kvm_vcpu *vcpu)
{
	return test_bit(vcpu->vcpu_id, vcpu->kvm->arch.float_int.idle_mask);
}