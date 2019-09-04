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
struct mmu_gather {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_tlb_mm (int /*<<< orphan*/ ) ; 

void tlb_flush(struct mmu_gather *tlb)
{
	flush_tlb_mm(tlb->mm);
}