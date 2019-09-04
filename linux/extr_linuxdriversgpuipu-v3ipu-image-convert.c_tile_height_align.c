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
typedef  enum ipu_image_convert_type { ____Placeholder_ipu_image_convert_type } ipu_image_convert_type ;

/* Variables and functions */
 int IMAGE_CONVERT_OUT ; 
 scalar_t__ ipu_rot_mode_is_irt (int) ; 

__attribute__((used)) static inline u32 tile_height_align(enum ipu_image_convert_type type,
				    enum ipu_rotate_mode rot_mode)
{
	return (type == IMAGE_CONVERT_OUT &&
		ipu_rot_mode_is_irt(rot_mode)) ? 8 : 2;
}