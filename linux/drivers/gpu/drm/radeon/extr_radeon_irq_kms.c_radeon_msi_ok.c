#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radeon_device {scalar_t__ family; int flags; TYPE_1__* pdev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int no_64bit_msi; int device; int subsystem_vendor; int subsystem_device; } ;

/* Variables and functions */
 scalar_t__ CHIP_BONAIRE ; 
 scalar_t__ CHIP_PALM ; 
 scalar_t__ CHIP_RS690 ; 
 scalar_t__ CHIP_RV380 ; 
 scalar_t__ CHIP_RV515 ; 
 int RADEON_IS_AGP ; 
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int radeon_msi ; 

__attribute__((used)) static bool radeon_msi_ok(struct radeon_device *rdev)
{
	/* RV370/RV380 was first asic with MSI support */
	if (rdev->family < CHIP_RV380)
		return false;

	/* MSIs don't work on AGP */
	if (rdev->flags & RADEON_IS_AGP)
		return false;

	/*
	 * Older chips have a HW limitation, they can only generate 40 bits
	 * of address for "64-bit" MSIs which breaks on some platforms, notably
	 * IBM POWER servers, so we limit them
	 */
	if (rdev->family < CHIP_BONAIRE) {
		dev_info(rdev->dev, "radeon: MSI limited to 32-bit\n");
		rdev->pdev->no_64bit_msi = 1;
	}

	/* force MSI on */
	if (radeon_msi == 1)
		return true;
	else if (radeon_msi == 0)
		return false;

	/* Quirks */
	/* HP RS690 only seems to work with MSIs. */
	if ((rdev->pdev->device == 0x791f) &&
	    (rdev->pdev->subsystem_vendor == 0x103c) &&
	    (rdev->pdev->subsystem_device == 0x30c2))
		return true;

	/* Dell RS690 only seems to work with MSIs. */
	if ((rdev->pdev->device == 0x791f) &&
	    (rdev->pdev->subsystem_vendor == 0x1028) &&
	    (rdev->pdev->subsystem_device == 0x01fc))
		return true;

	/* Dell RS690 only seems to work with MSIs. */
	if ((rdev->pdev->device == 0x791f) &&
	    (rdev->pdev->subsystem_vendor == 0x1028) &&
	    (rdev->pdev->subsystem_device == 0x01fd))
		return true;

	/* Gateway RS690 only seems to work with MSIs. */
	if ((rdev->pdev->device == 0x791f) &&
	    (rdev->pdev->subsystem_vendor == 0x107b) &&
	    (rdev->pdev->subsystem_device == 0x0185))
		return true;

	/* try and enable MSIs by default on all RS690s */
	if (rdev->family == CHIP_RS690)
		return true;

	/* RV515 seems to have MSI issues where it loses
	 * MSI rearms occasionally. This leads to lockups and freezes.
	 * disable it by default.
	 */
	if (rdev->family == CHIP_RV515)
		return false;
	if (rdev->flags & RADEON_IS_IGP) {
		/* APUs work fine with MSIs */
		if (rdev->family >= CHIP_PALM)
			return true;
		/* lots of IGPs have problems with MSIs */
		return false;
	}

	return true;
}