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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  enum mmu_prefetch_mode { ____Placeholder_mmu_prefetch_mode } mmu_prefetch_mode ;

/* Variables and functions */
 scalar_t__ MALIDP_MMU_CTRL_EN ; 
 scalar_t__ MALIDP_MMU_CTRL_MODE ; 
 scalar_t__ MALIDP_MMU_CTRL_PP_NUM_REQ (int) ; 
 scalar_t__ MALIDP_MMU_CTRL_PX_PS (int) ; 
 int MALIDP_PREFETCH_MODE_NONE ; 
 int MALIDP_PREFETCH_MODE_PARTIAL ; 
 scalar_t__ SZ_2M ; 
 scalar_t__ SZ_64K ; 

__attribute__((used)) static u32 malidp_calc_mmu_control_value(enum mmu_prefetch_mode mode,
					 u8 readahead, u8 n_planes, u32 pgsize)
{
	u32 mmu_ctrl = 0;

	if (mode != MALIDP_PREFETCH_MODE_NONE) {
		mmu_ctrl |= MALIDP_MMU_CTRL_EN;

		if (mode == MALIDP_PREFETCH_MODE_PARTIAL) {
			mmu_ctrl |= MALIDP_MMU_CTRL_MODE;
			mmu_ctrl |= MALIDP_MMU_CTRL_PP_NUM_REQ(readahead);
		}

		if (pgsize == SZ_64K || pgsize == SZ_2M) {
			int i;

			for (i = 0; i < n_planes; i++)
				mmu_ctrl |= MALIDP_MMU_CTRL_PX_PS(i);
		}
	}

	return mmu_ctrl;
}