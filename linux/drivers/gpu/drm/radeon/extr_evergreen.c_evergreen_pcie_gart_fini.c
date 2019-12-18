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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evergreen_pcie_gart_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_gart_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_gart_table_vram_free (struct radeon_device*) ; 

__attribute__((used)) static void evergreen_pcie_gart_fini(struct radeon_device *rdev)
{
	evergreen_pcie_gart_disable(rdev);
	radeon_gart_table_vram_free(rdev);
	radeon_gart_fini(rdev);
}