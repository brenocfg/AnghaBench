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
struct intel_ppat {int max_entries; int /*<<< orphan*/  clear_value; int /*<<< orphan*/  match; int /*<<< orphan*/  update_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHV_PPAT_SNOOP ; 
 int /*<<< orphan*/  __alloc_ppat_entry (struct intel_ppat*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdw_private_pat_update_hw ; 
 int /*<<< orphan*/  chv_private_pat_match ; 

__attribute__((used)) static void chv_setup_private_ppat(struct intel_ppat *ppat)
{
	ppat->max_entries = 8;
	ppat->update_hw = bdw_private_pat_update_hw;
	ppat->match = chv_private_pat_match;
	ppat->clear_value = CHV_PPAT_SNOOP;

	/*
	 * Map WB on BDW to snooped on CHV.
	 *
	 * Only the snoop bit has meaning for CHV, the rest is
	 * ignored.
	 *
	 * The hardware will never snoop for certain types of accesses:
	 * - CPU GTT (GMADR->GGTT->no snoop->memory)
	 * - PPGTT page tables
	 * - some other special cycles
	 *
	 * As with BDW, we also need to consider the following for GT accesses:
	 * "For GGTT, there is NO pat_sel[2:0] from the entry,
	 * so RTL will always use the value corresponding to
	 * pat_sel = 000".
	 * Which means we must set the snoop bit in PAT entry 0
	 * in order to keep the global status page working.
	 */

	__alloc_ppat_entry(ppat, 0, CHV_PPAT_SNOOP);
	__alloc_ppat_entry(ppat, 1, 0);
	__alloc_ppat_entry(ppat, 2, 0);
	__alloc_ppat_entry(ppat, 3, 0);
	__alloc_ppat_entry(ppat, 4, CHV_PPAT_SNOOP);
	__alloc_ppat_entry(ppat, 5, CHV_PPAT_SNOOP);
	__alloc_ppat_entry(ppat, 6, CHV_PPAT_SNOOP);
	__alloc_ppat_entry(ppat, 7, CHV_PPAT_SNOOP);
}