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
struct kvm_rmap_head {int dummy; } ;
struct TYPE_2__ {struct kvm_rmap_head** rmap; } ;
struct kvm_memory_slot {TYPE_1__ arch; int /*<<< orphan*/  base_gfn; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int PT_PAGE_TABLE_LEVEL ; 
 unsigned long gfn_to_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct kvm_rmap_head *__gfn_to_rmap(gfn_t gfn, int level,
					   struct kvm_memory_slot *slot)
{
	unsigned long idx;

	idx = gfn_to_index(gfn, slot->base_gfn, level);
	return &slot->arch.rmap[level - PT_PAGE_TABLE_LEVEL][idx];
}