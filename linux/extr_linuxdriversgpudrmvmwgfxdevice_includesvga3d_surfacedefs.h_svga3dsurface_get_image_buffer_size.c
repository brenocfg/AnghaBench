#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ surf_size_struct ;
struct svga3d_surface_desc {int /*<<< orphan*/  bytes_per_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  clamped_umul32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svga3dsurface_calculate_pitch (struct svga3d_surface_desc const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  svga3dsurface_get_size_in_blocks (struct svga3d_surface_desc const*,TYPE_1__ const*,TYPE_1__*) ; 
 scalar_t__ svga3dsurface_is_planar_surface (struct svga3d_surface_desc const*) ; 

__attribute__((used)) static inline u32
svga3dsurface_get_image_buffer_size(const struct svga3d_surface_desc *desc,
				    const surf_size_struct *size,
				    u32 pitch)
{
	surf_size_struct image_blocks;
	u32 slice_size, total_size;

	svga3dsurface_get_size_in_blocks(desc, size, &image_blocks);

	if (svga3dsurface_is_planar_surface(desc)) {
		total_size = clamped_umul32(image_blocks.width,
					    image_blocks.height);
		total_size = clamped_umul32(total_size, image_blocks.depth);
		total_size = clamped_umul32(total_size, desc->bytes_per_block);
		return total_size;
	}

	if (pitch == 0)
		pitch = svga3dsurface_calculate_pitch(desc, size);

	slice_size = clamped_umul32(image_blocks.height, pitch);
	total_size = clamped_umul32(slice_size, image_blocks.depth);

	return total_size;
}