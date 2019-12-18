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
struct qxl_device {int dummy; } ;
struct drm_minor {int /*<<< orphan*/  debugfs_root; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  QXL_DEBUGFS_ENTRIES ; 
 int /*<<< orphan*/  drm_debugfs_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_minor*) ; 
 int /*<<< orphan*/  qxl_debugfs_list ; 
 int qxl_ttm_debugfs_init (struct qxl_device*) ; 

int
qxl_debugfs_init(struct drm_minor *minor)
{
#if defined(CONFIG_DEBUG_FS)
	int r;
	struct qxl_device *dev =
		(struct qxl_device *) minor->dev->dev_private;

	drm_debugfs_create_files(qxl_debugfs_list, QXL_DEBUGFS_ENTRIES,
				 minor->debugfs_root, minor);

	r = qxl_ttm_debugfs_init(dev);
	if (r) {
		DRM_ERROR("Failed to init TTM debugfs\n");
		return r;
	}
#endif
	return 0;
}