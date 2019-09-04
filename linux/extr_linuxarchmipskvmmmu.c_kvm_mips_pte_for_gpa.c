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
struct kvm_mmu_memory_cache {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pgd; } ;
struct TYPE_4__ {TYPE_1__ gpa_mm; } ;
struct kvm {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/ * kvm_mips_walk_pgd (int /*<<< orphan*/ ,struct kvm_mmu_memory_cache*,unsigned long) ; 

__attribute__((used)) static pte_t *kvm_mips_pte_for_gpa(struct kvm *kvm,
				   struct kvm_mmu_memory_cache *cache,
				   unsigned long addr)
{
	return kvm_mips_walk_pgd(kvm->arch.gpa_mm.pgd, cache, addr);
}