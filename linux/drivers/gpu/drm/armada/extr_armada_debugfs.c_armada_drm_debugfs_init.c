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
struct drm_minor {int /*<<< orphan*/  debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARMADA_DEBUGFS_ENTRIES ; 
 int /*<<< orphan*/  armada_debugfs_list ; 
 int /*<<< orphan*/  drm_debugfs_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_minor*) ; 

int armada_drm_debugfs_init(struct drm_minor *minor)
{
	drm_debugfs_create_files(armada_debugfs_list, ARMADA_DEBUGFS_ENTRIES,
				 minor->debugfs_root, minor);

	return 0;
}