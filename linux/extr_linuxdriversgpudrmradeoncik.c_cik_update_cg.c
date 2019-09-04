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
typedef  int u32 ;
struct radeon_device {int flags; scalar_t__ has_uvd; } ;

/* Variables and functions */
 int RADEON_CG_BLOCK_BIF ; 
 int RADEON_CG_BLOCK_GFX ; 
 int RADEON_CG_BLOCK_HDP ; 
 int RADEON_CG_BLOCK_MC ; 
 int RADEON_CG_BLOCK_SDMA ; 
 int RADEON_CG_BLOCK_UVD ; 
 int RADEON_CG_BLOCK_VCE ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  cik_enable_bif_mgls (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_cgcg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_gui_idle_interrupt (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_hdp_ls (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_hdp_mgcg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_mc_ls (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_mc_mgcg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_mgcg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_sdma_mgcg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_sdma_mgls (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_uvd_mgcg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  vce_v2_0_enable_mgcg (struct radeon_device*,int) ; 

void cik_update_cg(struct radeon_device *rdev,
		   u32 block, bool enable)
{

	if (block & RADEON_CG_BLOCK_GFX) {
		cik_enable_gui_idle_interrupt(rdev, false);
		/* order matters! */
		if (enable) {
			cik_enable_mgcg(rdev, true);
			cik_enable_cgcg(rdev, true);
		} else {
			cik_enable_cgcg(rdev, false);
			cik_enable_mgcg(rdev, false);
		}
		cik_enable_gui_idle_interrupt(rdev, true);
	}

	if (block & RADEON_CG_BLOCK_MC) {
		if (!(rdev->flags & RADEON_IS_IGP)) {
			cik_enable_mc_mgcg(rdev, enable);
			cik_enable_mc_ls(rdev, enable);
		}
	}

	if (block & RADEON_CG_BLOCK_SDMA) {
		cik_enable_sdma_mgcg(rdev, enable);
		cik_enable_sdma_mgls(rdev, enable);
	}

	if (block & RADEON_CG_BLOCK_BIF) {
		cik_enable_bif_mgls(rdev, enable);
	}

	if (block & RADEON_CG_BLOCK_UVD) {
		if (rdev->has_uvd)
			cik_enable_uvd_mgcg(rdev, enable);
	}

	if (block & RADEON_CG_BLOCK_HDP) {
		cik_enable_hdp_mgcg(rdev, enable);
		cik_enable_hdp_ls(rdev, enable);
	}

	if (block & RADEON_CG_BLOCK_VCE) {
		vce_v2_0_enable_mgcg(rdev, enable);
	}
}