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
typedef  scalar_t__ u16 ;
struct radeon_device {scalar_t__ family; struct drm_device* ddev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_RS400 ; 
 int /*<<< orphan*/  COMBIOS_INTEGRATED_SYSTEM_INFO_TABLE ; 
 scalar_t__ RBIOS16 (scalar_t__) ; 
 scalar_t__ combios_get_table_offset (struct drm_device*,int /*<<< orphan*/ ) ; 

bool radeon_combios_sideport_present(struct radeon_device *rdev)
{
	struct drm_device *dev = rdev->ddev;
	u16 igp_info;

	/* sideport is AMD only */
	if (rdev->family == CHIP_RS400)
		return false;

	igp_info = combios_get_table_offset(dev, COMBIOS_INTEGRATED_SYSTEM_INFO_TABLE);

	if (igp_info) {
		if (RBIOS16(igp_info + 0x4))
			return true;
	}
	return false;
}