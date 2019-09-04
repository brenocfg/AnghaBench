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
struct TYPE_2__ {scalar_t__ direct; } ;
struct kvm_mmu_page {scalar_t__* gfns; TYPE_1__ role; } ;
typedef  scalar_t__ gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ kvm_mmu_page_get_gfn (struct kvm_mmu_page*,int) ; 

__attribute__((used)) static void kvm_mmu_page_set_gfn(struct kvm_mmu_page *sp, int index, gfn_t gfn)
{
	if (sp->role.direct)
		BUG_ON(gfn != kvm_mmu_page_get_gfn(sp, index));
	else
		sp->gfns[index] = gfn;
}