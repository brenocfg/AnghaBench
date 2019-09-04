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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_format_info {int num_planes; } ;

/* Variables and functions */
 struct drm_format_info* drm_format_info (int /*<<< orphan*/ ) ; 

int drm_format_num_planes(uint32_t format)
{
	const struct drm_format_info *info;

	info = drm_format_info(format);
	return info ? info->num_planes : 1;
}