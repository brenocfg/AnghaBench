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
struct intel_ppat {int max_entries; int clear_value; int /*<<< orphan*/  i915; int /*<<< orphan*/  match; int /*<<< orphan*/  update_hw; } ;

/* Variables and functions */
 int GEN8_PPAT_AGE (int) ; 
 int GEN8_PPAT_LLC ; 
 int GEN8_PPAT_LLCELLC ; 
 int GEN8_PPAT_UC ; 
 int GEN8_PPAT_WB ; 
 int GEN8_PPAT_WC ; 
 int GEN8_PPAT_WT ; 
 int /*<<< orphan*/  USES_PPGTT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __alloc_ppat_entry (struct intel_ppat*,int,int) ; 
 int /*<<< orphan*/  bdw_private_pat_match ; 
 int /*<<< orphan*/  bdw_private_pat_update_hw ; 

__attribute__((used)) static void bdw_setup_private_ppat(struct intel_ppat *ppat)
{
	ppat->max_entries = 8;
	ppat->update_hw = bdw_private_pat_update_hw;
	ppat->match = bdw_private_pat_match;
	ppat->clear_value = GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(3);

	if (!USES_PPGTT(ppat->i915)) {
		/* Spec: "For GGTT, there is NO pat_sel[2:0] from the entry,
		 * so RTL will always use the value corresponding to
		 * pat_sel = 000".
		 * So let's disable cache for GGTT to avoid screen corruptions.
		 * MOCS still can be used though.
		 * - System agent ggtt writes (i.e. cpu gtt mmaps) already work
		 * before this patch, i.e. the same uncached + snooping access
		 * like on gen6/7 seems to be in effect.
		 * - So this just fixes blitter/render access. Again it looks
		 * like it's not just uncached access, but uncached + snooping.
		 * So we can still hold onto all our assumptions wrt cpu
		 * clflushing on LLC machines.
		 */
		__alloc_ppat_entry(ppat, 0, GEN8_PPAT_UC);
		return;
	}

	__alloc_ppat_entry(ppat, 0, GEN8_PPAT_WB | GEN8_PPAT_LLC);      /* for normal objects, no eLLC */
	__alloc_ppat_entry(ppat, 1, GEN8_PPAT_WC | GEN8_PPAT_LLCELLC);  /* for something pointing to ptes? */
	__alloc_ppat_entry(ppat, 2, GEN8_PPAT_WT | GEN8_PPAT_LLCELLC);  /* for scanout with eLLC */
	__alloc_ppat_entry(ppat, 3, GEN8_PPAT_UC);                      /* Uncached objects, mostly for scanout */
	__alloc_ppat_entry(ppat, 4, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(0));
	__alloc_ppat_entry(ppat, 5, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(1));
	__alloc_ppat_entry(ppat, 6, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(2));
	__alloc_ppat_entry(ppat, 7, GEN8_PPAT_WB | GEN8_PPAT_LLCELLC | GEN8_PPAT_AGE(3));
}