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
 int /*<<< orphan*/  cik_update_gfx_pg (struct radeon_device*,int) ; 

__attribute__((used)) static void cik_fini_pg(struct radeon_device *rdev)
{
	if (rdev->pg_flags) {
		cik_update_gfx_pg(rdev, false);
		if (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG) {
			cik_enable_cp_pg(rdev, false);
			cik_enable_gds_pg(rdev, false);
		}
	}
}