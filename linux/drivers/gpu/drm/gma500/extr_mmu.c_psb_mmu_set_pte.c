#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct psb_mmu_pt {int /*<<< orphan*/ * v; } ;

/* Variables and functions */
 size_t psb_mmu_pt_index (unsigned long) ; 

__attribute__((used)) static inline void psb_mmu_set_pte(struct psb_mmu_pt *pt, unsigned long addr,
				   uint32_t pte)
{
	pt->v[psb_mmu_pt_index(addr)] = pte;
}