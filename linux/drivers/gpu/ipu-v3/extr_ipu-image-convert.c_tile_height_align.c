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
struct ipu_image_pixfmt {int uv_width_dec; int /*<<< orphan*/  uv_packed; scalar_t__ planar; } ;
typedef  enum ipu_rotate_mode { ____Placeholder_ipu_rotate_mode } ipu_rotate_mode ;
typedef  enum ipu_image_convert_type { ____Placeholder_ipu_image_convert_type } ipu_image_convert_type ;

/* Variables and functions */
 int IMAGE_CONVERT_IN ; 
 int /*<<< orphan*/  ipu_rot_mode_is_irt (int) ; 

__attribute__((used)) static inline u32 tile_height_align(enum ipu_image_convert_type type,
				    const struct ipu_image_pixfmt *fmt,
				    enum ipu_rotate_mode rot_mode)
{
	if (type == IMAGE_CONVERT_IN || !ipu_rot_mode_is_irt(rot_mode))
		return 2;

	/*
	 * Align to 16x16 pixel blocks for planar 4:2:0 chroma subsampled
	 * formats to guarantee 8-byte aligned line start addresses in the
	 * chroma planes when IRT is used. Align to 8x8 pixel IRT block size
	 * for all other formats.
	 */
	return (fmt->planar && !fmt->uv_packed) ? 8 * fmt->uv_width_dec : 8;
}