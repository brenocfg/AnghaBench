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
struct radeon_device {int pg_flags; } ;

/* Variables and functions */
 int RADEON_PG_SUPPORT_GFX_PG ; 
 int /*<<< orphan*/  cik_enable_cp_pg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_gds_pg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_sck_slowdown_on_pd (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_enable_sck_slowdown_on_pu (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_init_ao_cu_mask (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_init_gfx_cgpg (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_update_gfx_pg (struct radeon_device*,int) ; 

__attribute__((used)) static void cik_init_pg(struct radeon_device *rdev)
{
	if (rdev->pg_flags) {
		cik_enable_sck_slowdown_on_pu(rdev, true);
		cik_enable_sck_slowdown_on_pd(rdev, true);
		if (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG) {
			cik_init_gfx_cgpg(rdev);
			cik_enable_cp_pg(rdev, true);
			cik_enable_gds_pg(rdev, true);
		}
		cik_init_ao_cu_mask(rdev);
		cik_update_gfx_pg(rdev, true);
	}
}