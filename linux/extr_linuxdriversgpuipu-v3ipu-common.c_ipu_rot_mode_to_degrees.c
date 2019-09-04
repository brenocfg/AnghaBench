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
typedef  enum ipu_rotate_mode { ____Placeholder_ipu_rotate_mode } ipu_rotate_mode ;

/* Variables and functions */
 int EINVAL ; 
#define  IPU_ROTATE_180 131 
#define  IPU_ROTATE_90_LEFT 130 
#define  IPU_ROTATE_90_RIGHT 129 
#define  IPU_ROTATE_NONE 128 

int ipu_rot_mode_to_degrees(int *degrees, enum ipu_rotate_mode mode,
			    bool hflip, bool vflip)
{
	u32 r90, vf, hf;

	r90 = ((u32)mode >> 2) & 0x1;
	hf = ((u32)mode >> 1) & 0x1;
	vf = ((u32)mode >> 0) & 0x1;
	hf ^= (u32)hflip;
	vf ^= (u32)vflip;

	switch ((enum ipu_rotate_mode)((r90 << 2) | (hf << 1) | vf)) {
	case IPU_ROTATE_NONE:
		*degrees = 0;
		break;
	case IPU_ROTATE_90_RIGHT:
		*degrees = 90;
		break;
	case IPU_ROTATE_180:
		*degrees = 180;
		break;
	case IPU_ROTATE_90_LEFT:
		*degrees = 270;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}