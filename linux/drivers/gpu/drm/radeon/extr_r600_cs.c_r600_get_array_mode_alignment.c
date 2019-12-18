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
typedef  int u64 ;
typedef  int u32 ;
struct array_mode_checker {int nbanks; int npipes; int blocksize; int nsamples; int array_mode; int group_size; } ;

/* Variables and functions */
#define  ARRAY_1D_TILED_THIN1 131 
#define  ARRAY_2D_TILED_THIN1 130 
#define  ARRAY_LINEAR_ALIGNED 129 
#define  ARRAY_LINEAR_GENERAL 128 
 int EINVAL ; 
 void* max (int,int) ; 

__attribute__((used)) static int r600_get_array_mode_alignment(struct array_mode_checker *values,
						u32 *pitch_align,
						u32 *height_align,
						u32 *depth_align,
						u64 *base_align)
{
	u32 tile_width = 8;
	u32 tile_height = 8;
	u32 macro_tile_width = values->nbanks;
	u32 macro_tile_height = values->npipes;
	u32 tile_bytes = tile_width * tile_height * values->blocksize * values->nsamples;
	u32 macro_tile_bytes = macro_tile_width * macro_tile_height * tile_bytes;

	switch (values->array_mode) {
	case ARRAY_LINEAR_GENERAL:
		/* technically tile_width/_height for pitch/height */
		*pitch_align = 1; /* tile_width */
		*height_align = 1; /* tile_height */
		*depth_align = 1;
		*base_align = 1;
		break;
	case ARRAY_LINEAR_ALIGNED:
		*pitch_align = max((u32)64, (u32)(values->group_size / values->blocksize));
		*height_align = 1;
		*depth_align = 1;
		*base_align = values->group_size;
		break;
	case ARRAY_1D_TILED_THIN1:
		*pitch_align = max((u32)tile_width,
				   (u32)(values->group_size /
					 (tile_height * values->blocksize * values->nsamples)));
		*height_align = tile_height;
		*depth_align = 1;
		*base_align = values->group_size;
		break;
	case ARRAY_2D_TILED_THIN1:
		*pitch_align = max((u32)macro_tile_width * tile_width,
				(u32)((values->group_size * values->nbanks) /
				(values->blocksize * values->nsamples * tile_width)));
		*height_align = macro_tile_height * tile_height;
		*depth_align = 1;
		*base_align = max(macro_tile_bytes,
				  (*pitch_align) * values->blocksize * (*height_align) * values->nsamples);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}