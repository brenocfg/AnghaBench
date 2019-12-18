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

/* Variables and functions */
 int /*<<< orphan*/  DRM_MAJOR ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_ida_destroy () ; 
 int /*<<< orphan*/  drm_debugfs_root ; 
 int /*<<< orphan*/  drm_minors_idr ; 
 int /*<<< orphan*/  drm_sysfs_destroy () ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void drm_core_exit(void)
{
	unregister_chrdev(DRM_MAJOR, "drm");
	debugfs_remove(drm_debugfs_root);
	drm_sysfs_destroy();
	idr_destroy(&drm_minors_idr);
	drm_connector_ida_destroy();
}