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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  DRM_MODE_REFLECT_X 129 
#define  DRM_MODE_REFLECT_Y 128 
 int /*<<< orphan*/  MISSING_CASE (unsigned int) ; 
 int /*<<< orphan*/  PLANE_CTL_FLIP_HORIZONTAL ; 

__attribute__((used)) static u32 cnl_plane_ctl_flip(unsigned int reflect)
{
	switch (reflect) {
	case 0:
		break;
	case DRM_MODE_REFLECT_X:
		return PLANE_CTL_FLIP_HORIZONTAL;
	case DRM_MODE_REFLECT_Y:
	default:
		MISSING_CASE(reflect);
	}

	return 0;
}