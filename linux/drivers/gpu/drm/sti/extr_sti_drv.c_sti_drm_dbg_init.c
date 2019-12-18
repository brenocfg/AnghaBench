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
struct drm_minor {int /*<<< orphan*/  dev; int /*<<< orphan*/  debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ) ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_debugfs_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_minor*) ; 
 int /*<<< orphan*/  sti_drm_dbg_list ; 
 int /*<<< orphan*/  sti_drm_fps_fops ; 

__attribute__((used)) static int sti_drm_dbg_init(struct drm_minor *minor)
{
	int ret;

	ret = drm_debugfs_create_files(sti_drm_dbg_list,
				       ARRAY_SIZE(sti_drm_dbg_list),
				       minor->debugfs_root, minor);
	if (ret)
		goto err;

	debugfs_create_file("fps_show", S_IRUGO | S_IWUSR, minor->debugfs_root,
			    minor->dev, &sti_drm_fps_fops);

	DRM_INFO("%s: debugfs installed\n", DRIVER_NAME);
	return 0;
err:
	DRM_ERROR("%s: cannot install debugfs\n", DRIVER_NAME);
	return ret;
}