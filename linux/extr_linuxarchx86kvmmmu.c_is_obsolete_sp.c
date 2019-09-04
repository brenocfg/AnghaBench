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
struct kvm_mmu_page {scalar_t__ mmu_valid_gen; } ;
struct TYPE_2__ {scalar_t__ mmu_valid_gen; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int unlikely (int) ; 

__attribute__((used)) static bool is_obsolete_sp(struct kvm *kvm, struct kvm_mmu_page *sp)
{
	return unlikely(sp->mmu_valid_gen != kvm->arch.mmu_valid_gen);
}