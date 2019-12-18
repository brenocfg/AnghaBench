#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_minor {int /*<<< orphan*/  debugfs_root; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct drm_minor* primary; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/ * fops; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  I915_DEBUGFS_ENTRIES ; 
 int S_IRUGO ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_debugfs_create_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_minor*) ; 
 TYPE_2__* i915_debugfs_files ; 
 int /*<<< orphan*/  i915_debugfs_list ; 
 int /*<<< orphan*/  i915_forcewake_fops ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 

int i915_debugfs_register(struct drm_i915_private *dev_priv)
{
	struct drm_minor *minor = dev_priv->drm.primary;
	int i;

	debugfs_create_file("i915_forcewake_user", S_IRUSR, minor->debugfs_root,
			    to_i915(minor->dev), &i915_forcewake_fops);

	for (i = 0; i < ARRAY_SIZE(i915_debugfs_files); i++) {
		debugfs_create_file(i915_debugfs_files[i].name,
				    S_IRUGO | S_IWUSR,
				    minor->debugfs_root,
				    to_i915(minor->dev),
				    i915_debugfs_files[i].fops);
	}

	return drm_debugfs_create_files(i915_debugfs_list,
					I915_DEBUGFS_ENTRIES,
					minor->debugfs_root, minor);
}