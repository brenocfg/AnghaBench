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
struct radeon_device {int flags; scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_BARTS ; 
 scalar_t__ CHIP_R600 ; 
 scalar_t__ CHIP_RS600 ; 
 scalar_t__ CHIP_RV770 ; 
 int RADEON_IS_IGP ; 
 int avivo_read_disabled_bios (struct radeon_device*) ; 
 int igp_read_bios_from_vram (struct radeon_device*) ; 
 int legacy_read_disabled_bios (struct radeon_device*) ; 
 int ni_read_disabled_bios (struct radeon_device*) ; 
 int r600_read_disabled_bios (struct radeon_device*) ; 
 int r700_read_disabled_bios (struct radeon_device*) ; 

__attribute__((used)) static bool radeon_read_disabled_bios(struct radeon_device *rdev)
{
	if (rdev->flags & RADEON_IS_IGP)
		return igp_read_bios_from_vram(rdev);
	else if (rdev->family >= CHIP_BARTS)
		return ni_read_disabled_bios(rdev);
	else if (rdev->family >= CHIP_RV770)
		return r700_read_disabled_bios(rdev);
	else if (rdev->family >= CHIP_R600)
		return r600_read_disabled_bios(rdev);
	else if (rdev->family >= CHIP_RS600)
		return avivo_read_disabled_bios(rdev);
	else
		return legacy_read_disabled_bios(rdev);
}