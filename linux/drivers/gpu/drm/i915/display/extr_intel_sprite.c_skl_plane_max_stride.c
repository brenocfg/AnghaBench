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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_plane {int dummy; } ;
struct drm_format_info {int* cpp; } ;

/* Variables and functions */
 struct drm_format_info* drm_format_info (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 unsigned int min (int,int) ; 

__attribute__((used)) static unsigned int
skl_plane_max_stride(struct intel_plane *plane,
		     u32 pixel_format, u64 modifier,
		     unsigned int rotation)
{
	const struct drm_format_info *info = drm_format_info(pixel_format);
	int cpp = info->cpp[0];

	/*
	 * "The stride in bytes must not exceed the
	 * of the size of 8K pixels and 32K bytes."
	 */
	if (drm_rotation_90_or_270(rotation))
		return min(8192, 32768 / cpp);
	else
		return min(8192 * cpp, 32768);
}