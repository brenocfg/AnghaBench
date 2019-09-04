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
 int /*<<< orphan*/  VC4_DEBUGFS_ENTRIES ; 
 int drm_debugfs_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_minor*) ; 
 int /*<<< orphan*/  vc4_debugfs_list ; 

int
vc4_debugfs_init(struct drm_minor *minor)
{
	return drm_debugfs_create_files(vc4_debugfs_list, VC4_DEBUGFS_ENTRIES,
					minor->debugfs_root, minor);
}