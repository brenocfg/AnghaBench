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
struct TYPE_2__ {int gtt_size; } ;
struct radeon_device {TYPE_1__ mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 

void rs400_gart_adjust_size(struct radeon_device *rdev)
{
	/* Check gart size */
	switch (rdev->mc.gtt_size/(1024*1024)) {
	case 32:
	case 64:
	case 128:
	case 256:
	case 512:
	case 1024:
	case 2048:
		break;
	default:
		DRM_ERROR("Unable to use IGP GART size %uM\n",
			  (unsigned)(rdev->mc.gtt_size >> 20));
		DRM_ERROR("Valid GART size for IGP are 32M,64M,128M,256M,512M,1G,2G\n");
		DRM_ERROR("Forcing to 32M GART size\n");
		rdev->mc.gtt_size = 32 * 1024 * 1024;
		return;
	}
}