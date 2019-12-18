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
typedef  int u32 ;

/* Variables and functions */
 int DRM_MODE_REFLECT_X ; 
 int DRM_MODE_REFLECT_Y ; 
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 int DRM_MODE_ROTATE_MASK ; 
 int L_HFLIP ; 
 int L_ROT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L_ROT_R0 ; 
 int /*<<< orphan*/  L_ROT_R180 ; 
 int /*<<< orphan*/  L_ROT_R270 ; 
 int /*<<< orphan*/  L_ROT_R90 ; 
 int L_VFLIP ; 

__attribute__((used)) static u32 to_rot_ctrl(u32 rot)
{
	u32 lr_ctrl = 0;

	switch (rot & DRM_MODE_ROTATE_MASK) {
	case DRM_MODE_ROTATE_0:
		lr_ctrl |= L_ROT(L_ROT_R0);
		break;
	case DRM_MODE_ROTATE_90:
		lr_ctrl |= L_ROT(L_ROT_R90);
		break;
	case DRM_MODE_ROTATE_180:
		lr_ctrl |= L_ROT(L_ROT_R180);
		break;
	case DRM_MODE_ROTATE_270:
		lr_ctrl |= L_ROT(L_ROT_R270);
		break;
	}

	if (rot & DRM_MODE_REFLECT_X)
		lr_ctrl |= L_HFLIP;
	if (rot & DRM_MODE_REFLECT_Y)
		lr_ctrl |= L_VFLIP;

	return lr_ctrl;
}