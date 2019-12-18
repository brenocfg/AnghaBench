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
typedef  int u64 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHV_PPAT_SNOOP ; 
 int GEN8_PPAT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN8_PRIVATE_PAT_HI ; 
 int /*<<< orphan*/  GEN8_PRIVATE_PAT_LO ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static void chv_setup_private_ppat(struct drm_i915_private *dev_priv)
{
	u64 pat;

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

	pat = GEN8_PPAT(0, CHV_PPAT_SNOOP) |
	      GEN8_PPAT(1, 0) |
	      GEN8_PPAT(2, 0) |
	      GEN8_PPAT(3, 0) |
	      GEN8_PPAT(4, CHV_PPAT_SNOOP) |
	      GEN8_PPAT(5, CHV_PPAT_SNOOP) |
	      GEN8_PPAT(6, CHV_PPAT_SNOOP) |
	      GEN8_PPAT(7, CHV_PPAT_SNOOP);

	I915_WRITE(GEN8_PRIVATE_PAT_LO, lower_32_bits(pat));
	I915_WRITE(GEN8_PRIVATE_PAT_HI, upper_32_bits(pat));
}