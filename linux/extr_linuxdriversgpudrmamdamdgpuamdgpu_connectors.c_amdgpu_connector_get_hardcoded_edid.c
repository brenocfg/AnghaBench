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
struct edid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bios_hardcoded_edid_size; scalar_t__ bios_hardcoded_edid; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct edid* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct edid *
amdgpu_connector_get_hardcoded_edid(struct amdgpu_device *adev)
{
	struct edid *edid;

	if (adev->mode_info.bios_hardcoded_edid) {
		edid = kmalloc(adev->mode_info.bios_hardcoded_edid_size, GFP_KERNEL);
		if (edid) {
			memcpy((unsigned char *)edid,
			       (unsigned char *)adev->mode_info.bios_hardcoded_edid,
			       adev->mode_info.bios_hardcoded_edid_size);
			return edid;
		}
	}
	return NULL;
}