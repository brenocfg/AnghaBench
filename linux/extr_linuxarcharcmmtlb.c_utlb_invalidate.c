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

/* Variables and functions */

__attribute__((used)) static void utlb_invalidate(void)
{
#if (CONFIG_ARC_MMU_VER >= 2)

#if (CONFIG_ARC_MMU_VER == 2)
	/* MMU v2 introduced the uTLB Flush command.
	 * There was however an obscure hardware bug, where uTLB flush would
	 * fail when a prior probe for J-TLB (both totally unrelated) would
	 * return lkup err - because the entry didn't exist in MMU.
	 * The Workround was to set Index reg with some valid value, prior to
	 * flush. This was fixed in MMU v3 hence not needed any more
	 */
	unsigned int idx;

	/* make sure INDEX Reg is valid */
	idx = read_aux_reg(ARC_REG_TLBINDEX);

	/* If not write some dummy val */
	if (unlikely(idx & TLB_LKUP_ERR))
		write_aux_reg(ARC_REG_TLBINDEX, 0xa);
#endif

	write_aux_reg(ARC_REG_TLBCOMMAND, TLBIVUTLB);
#endif

}