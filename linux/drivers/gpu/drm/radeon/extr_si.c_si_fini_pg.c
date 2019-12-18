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
struct radeon_device {scalar_t__ pg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  si_enable_dma_pg (struct radeon_device*,int) ; 
 int /*<<< orphan*/  si_enable_gfx_cgpg (struct radeon_device*,int) ; 

__attribute__((used)) static void si_fini_pg(struct radeon_device *rdev)
{
	if (rdev->pg_flags) {
		si_enable_dma_pg(rdev, false);
		si_enable_gfx_cgpg(rdev, false);
	}
}