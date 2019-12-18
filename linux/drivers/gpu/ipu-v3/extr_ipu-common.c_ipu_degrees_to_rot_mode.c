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

int ipu_degrees_to_rot_mode(enum ipu_rotate_mode *mode, int degrees,
			    bool hflip, bool vflip)
{
	u32 r90, vf, hf;

	switch (degrees) {
	case 0:
		vf = hf = r90 = 0;
		break;
	case 90:
		vf = hf = 0;
		r90 = 1;
		break;
	case 180:
		vf = hf = 1;
		r90 = 0;
		break;
	case 270:
		vf = hf = r90 = 1;
		break;
	default:
		return -EINVAL;
	}

	hf ^= (u32)hflip;
	vf ^= (u32)vflip;

	*mode = (enum ipu_rotate_mode)((r90 << 2) | (hf << 1) | vf);
	return 0;
}