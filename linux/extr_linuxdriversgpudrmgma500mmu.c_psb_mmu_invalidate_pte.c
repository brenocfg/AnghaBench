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
struct psb_mmu_pt {TYPE_1__* pd; int /*<<< orphan*/ * v; } ;
struct TYPE_2__ {int /*<<< orphan*/  invalid_pte; } ;

/* Variables and functions */
 size_t psb_mmu_pt_index (unsigned long) ; 

__attribute__((used)) static inline void psb_mmu_invalidate_pte(struct psb_mmu_pt *pt,
					  unsigned long addr)
{
	pt->v[psb_mmu_pt_index(addr)] = pt->pd->invalid_pte;
}