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
struct TYPE_3__ {scalar_t__ mmio_gen; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;
struct TYPE_4__ {scalar_t__ generation; } ;

/* Variables and functions */
 TYPE_2__* kvm_memslots (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool vcpu_match_mmio_gen(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.mmio_gen == kvm_memslots(vcpu->kvm)->generation;
}