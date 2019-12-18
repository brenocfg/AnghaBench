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
 int ROTATION_ANGLE_180 ; 
 int ROTATION_ANGLE_270 ; 
 int ROTATION_ANGLE_90 ; 

__attribute__((used)) static inline void get_vp_scan_direction(
	enum dc_rotation_angle rotation,
	bool horizontal_mirror,
	bool *orthogonal_rotation,
	bool *flip_vert_scan_dir,
	bool *flip_horz_scan_dir)
{
	*orthogonal_rotation = false;
	*flip_vert_scan_dir = false;
	*flip_horz_scan_dir = false;
	if (rotation == ROTATION_ANGLE_180) {
		*flip_vert_scan_dir = true;
		*flip_horz_scan_dir = true;
	} else if (rotation == ROTATION_ANGLE_90) {
		*orthogonal_rotation = true;
		*flip_horz_scan_dir = true;
	} else if (rotation == ROTATION_ANGLE_270) {
		*orthogonal_rotation = true;
		*flip_vert_scan_dir = true;
	}

	if (horizontal_mirror)
		*flip_horz_scan_dir = !*flip_horz_scan_dir;
}