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
struct drm_format_info {int num_planes; unsigned int* block_h; } ;

/* Variables and functions */

unsigned int drm_format_info_block_height(const struct drm_format_info *info,
					  int plane)
{
	if (!info || plane < 0 || plane >= info->num_planes)
		return 0;

	if (!info->block_h[plane])
		return 1;
	return info->block_h[plane];
}