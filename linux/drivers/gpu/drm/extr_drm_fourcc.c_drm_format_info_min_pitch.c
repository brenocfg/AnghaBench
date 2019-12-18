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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u64 ;
struct drm_format_info {int num_planes; int* char_per_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP_ULL (int,int) ; 
 int drm_format_info_block_height (struct drm_format_info const*,int) ; 
 int drm_format_info_block_width (struct drm_format_info const*,int) ; 

uint64_t drm_format_info_min_pitch(const struct drm_format_info *info,
				   int plane, unsigned int buffer_width)
{
	if (!info || plane < 0 || plane >= info->num_planes)
		return 0;

	return DIV_ROUND_UP_ULL((u64)buffer_width * info->char_per_block[plane],
			    drm_format_info_block_width(info, plane) *
			    drm_format_info_block_height(info, plane));
}