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
struct intel_ppat {int max_entries; int clear_value; int /*<<< orphan*/  match; int /*<<< orphan*/  update_hw; } ;

/* Variables and functions */
 int GEN8_PPAT_AGE (int) ; 
 int GEN8_PPAT_LLC ; 
 int GEN8_PPAT_LLCELLC ; 
 int GEN8_PPAT_UC ; 
 int GEN8_PPAT_WB ; 
 int GEN8_PPAT_WC ; 
 int GEN8_PPAT_WT ; 
 int /*<<< orphan*/  __alloc_ppat_entry (struct intel_ppat*,int,int) ; 
 int /*<<< orphan*/  bdw_private_pat_match ; 
 int /*<<< orphan*/  cnl_private_pat_update_hw ; 

__attribute__((used)) static void cnl_setup_private_ppat(struct intel_ppat *ppat)
{
	ppat->max_entries = 8;
	ppat->update_hw = cnl_private_pat_update_hw;
	ppat->match = bdw_private_pat_match;
	ppat->clear_value = GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(3);

	__alloc_ppat_entry(ppat, 0, GEN8_PPAT_WB | GEN8_PPAT_LLC);
	__alloc_ppat_entry(ppat, 1, GEN8_PPAT_WC | GEN8_PPAT_LLCELLC);
	__alloc_ppat_entry(ppat, 2, GEN8_PPAT_WT | GEN8_PPAT_LLCELLC);
	__alloc_ppat_entry(ppat, 3, GEN8_PPAT_UC);
	__alloc_ppat_entry(ppat, 4, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(0));
	__alloc_ppat_entry(ppat, 5, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(1));
	__alloc_ppat_entry(ppat, 6, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(2));
	__alloc_ppat_entry(ppat, 7, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(3));
}