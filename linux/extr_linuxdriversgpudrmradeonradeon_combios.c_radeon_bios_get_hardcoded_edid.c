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
struct TYPE_2__ {int /*<<< orphan*/  bios_hardcoded_edid_size; scalar_t__ bios_hardcoded_edid; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct edid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct edid* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

struct edid *
radeon_bios_get_hardcoded_edid(struct radeon_device *rdev)
{
	struct edid *edid;

	if (rdev->mode_info.bios_hardcoded_edid) {
		edid = kmalloc(rdev->mode_info.bios_hardcoded_edid_size, GFP_KERNEL);
		if (edid) {
			memcpy((unsigned char *)edid,
			       (unsigned char *)rdev->mode_info.bios_hardcoded_edid,
			       rdev->mode_info.bios_hardcoded_edid_size);
			return edid;
		}
	}
	return NULL;
}