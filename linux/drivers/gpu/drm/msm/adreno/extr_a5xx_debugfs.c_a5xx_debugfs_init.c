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
struct msm_gpu {int dummy; } ;
struct drm_minor {int /*<<< orphan*/  debugfs_root; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  S_IWUGO ; 
 int /*<<< orphan*/  a5xx_debugfs_list ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_device*,int /*<<< orphan*/ *) ; 
 int drm_debugfs_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_minor*) ; 
 int /*<<< orphan*/  reset_fops ; 

int a5xx_debugfs_init(struct msm_gpu *gpu, struct drm_minor *minor)
{
	struct drm_device *dev;
	int ret;

	if (!minor)
		return 0;

	dev = minor->dev;

	ret = drm_debugfs_create_files(a5xx_debugfs_list,
			ARRAY_SIZE(a5xx_debugfs_list),
			minor->debugfs_root, minor);

	if (ret) {
		DRM_DEV_ERROR(dev->dev, "could not install a5xx_debugfs_list\n");
		return ret;
	}

	debugfs_create_file("reset", S_IWUGO, minor->debugfs_root, dev,
			    &reset_fops);

	return 0;
}