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
struct drm_format_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_FORMAT_NV12 ; 
 int /*<<< orphan*/  DRM_FORMAT_X0L0 ; 
 int /*<<< orphan*/  DRM_FORMAT_XRGB4444 ; 
 int /*<<< orphan*/  DRM_FORMAT_YUV422 ; 
 int /*<<< orphan*/  FAIL_ON (int) ; 
 struct drm_format_info* drm_format_info (int /*<<< orphan*/ ) ; 
 int drm_format_info_block_height (struct drm_format_info const*,int) ; 

int igt_check_drm_format_block_height(void *ignored)
{
	const struct drm_format_info *info = NULL;

	/* Test invalid arguments */
	FAIL_ON(drm_format_info_block_height(info, 0) != 0);
	FAIL_ON(drm_format_info_block_height(info, -1) != 0);
	FAIL_ON(drm_format_info_block_height(info, 1) != 0);

	/* Test 1 plane format */
	info = drm_format_info(DRM_FORMAT_XRGB4444);
	FAIL_ON(!info);
	FAIL_ON(drm_format_info_block_height(info, 0) != 1);
	FAIL_ON(drm_format_info_block_height(info, 1) != 0);
	FAIL_ON(drm_format_info_block_height(info, -1) != 0);

	/* Test 2 planes format */
	info = drm_format_info(DRM_FORMAT_NV12);
	FAIL_ON(!info);
	FAIL_ON(drm_format_info_block_height(info, 0) != 1);
	FAIL_ON(drm_format_info_block_height(info, 1) != 1);
	FAIL_ON(drm_format_info_block_height(info, 2) != 0);
	FAIL_ON(drm_format_info_block_height(info, -1) != 0);

	/* Test 3 planes format */
	info = drm_format_info(DRM_FORMAT_YUV422);
	FAIL_ON(!info);
	FAIL_ON(drm_format_info_block_height(info, 0) != 1);
	FAIL_ON(drm_format_info_block_height(info, 1) != 1);
	FAIL_ON(drm_format_info_block_height(info, 2) != 1);
	FAIL_ON(drm_format_info_block_height(info, 3) != 0);
	FAIL_ON(drm_format_info_block_height(info, -1) != 0);

	/* Test a tiled format */
	info = drm_format_info(DRM_FORMAT_X0L0);
	FAIL_ON(!info);
	FAIL_ON(drm_format_info_block_height(info, 0) != 2);
	FAIL_ON(drm_format_info_block_height(info, 1) != 0);
	FAIL_ON(drm_format_info_block_height(info, -1) != 0);

	return 0;
}