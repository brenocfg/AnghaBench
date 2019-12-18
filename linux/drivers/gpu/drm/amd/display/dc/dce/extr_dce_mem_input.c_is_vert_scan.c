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
typedef  enum dc_rotation_angle { ____Placeholder_dc_rotation_angle } dc_rotation_angle ;

/* Variables and functions */
#define  ROTATION_ANGLE_270 129 
#define  ROTATION_ANGLE_90 128 

__attribute__((used)) static bool is_vert_scan(enum dc_rotation_angle rotation)
{
	switch (rotation) {
	case ROTATION_ANGLE_90:
	case ROTATION_ANGLE_270:
		return true;
	default:
		return false;
	}
}