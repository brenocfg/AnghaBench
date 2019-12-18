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
struct TYPE_2__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ddev; TYPE_1__ mode_info; scalar_t__ is_atom_bios; scalar_t__ bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  atom_asic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ radeon_card_posted (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_combios_asic_init (int /*<<< orphan*/ ) ; 

bool radeon_boot_test_post_card(struct radeon_device *rdev)
{
	if (radeon_card_posted(rdev))
		return true;

	if (rdev->bios) {
		DRM_INFO("GPU not posted. posting now...\n");
		if (rdev->is_atom_bios)
			atom_asic_init(rdev->mode_info.atom_context);
		else
			radeon_combios_asic_init(rdev->ddev);
		return true;
	} else {
		dev_err(rdev->dev, "Card not posted and no BIOS - ignoring\n");
		return false;
	}
}