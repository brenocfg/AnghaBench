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
struct qxl_device {unsigned int debugfs_count; TYPE_1__* debugfs; } ;
struct drm_info_list {int dummy; } ;
struct TYPE_2__ {unsigned int num_files; struct drm_info_list* files; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 unsigned int QXL_DEBUGFS_MAX_COMPONENTS ; 

int qxl_debugfs_add_files(struct qxl_device *qdev,
			  struct drm_info_list *files,
			  unsigned nfiles)
{
	unsigned i;

	for (i = 0; i < qdev->debugfs_count; i++) {
		if (qdev->debugfs[i].files == files) {
			/* Already registered */
			return 0;
		}
	}

	i = qdev->debugfs_count + 1;
	if (i > QXL_DEBUGFS_MAX_COMPONENTS) {
		DRM_ERROR("Reached maximum number of debugfs components.\n");
		DRM_ERROR("Report so we increase QXL_DEBUGFS_MAX_COMPONENTS.\n");
		return -EINVAL;
	}
	qdev->debugfs[qdev->debugfs_count].files = files;
	qdev->debugfs[qdev->debugfs_count].num_files = nfiles;
	qdev->debugfs_count = i;
#if defined(CONFIG_DEBUG_FS)
	drm_debugfs_create_files(files, nfiles,
				 qdev->ddev.primary->debugfs_root,
				 qdev->ddev.primary);
#endif
	return 0;
}