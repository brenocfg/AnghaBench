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
typedef  int const u32 ;
struct TYPE_2__ {int width; int height; int depth; } ;
struct svga3d_surface_desc {int const bytes_per_block; TYPE_1__ block_size; } ;
typedef  int /*<<< orphan*/  SVGA3dSurfaceFormat ;

/* Variables and functions */
 int const __KERNEL_DIV_ROUND_UP (int const,int const) ; 
 struct svga3d_surface_desc* svga3dsurface_get_desc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32
svga3dsurface_get_pixel_offset(SVGA3dSurfaceFormat format,
			       u32 width, u32 height,
			       u32 x, u32 y, u32 z)
{
	const struct svga3d_surface_desc *desc = svga3dsurface_get_desc(format);
	const u32 bw = desc->block_size.width, bh = desc->block_size.height;
	const u32 bd = desc->block_size.depth;
	const u32 rowstride = __KERNEL_DIV_ROUND_UP(width, bw) *
			      desc->bytes_per_block;
	const u32 imgstride = __KERNEL_DIV_ROUND_UP(height, bh) * rowstride;
	const u32 offset = (z / bd * imgstride +
			    y / bh * rowstride +
			    x / bw * desc->bytes_per_block);
	return offset;
}