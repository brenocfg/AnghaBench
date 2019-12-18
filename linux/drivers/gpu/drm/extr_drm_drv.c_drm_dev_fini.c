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
struct drm_device {int /*<<< orphan*/  unique; int /*<<< orphan*/  struct_mutex; int /*<<< orphan*/  filelist_mutex; int /*<<< orphan*/  clientlist_mutex; int /*<<< orphan*/  master_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  anon_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_GEM ; 
 int /*<<< orphan*/  DRM_MINOR_PRIMARY ; 
 int /*<<< orphan*/  DRM_MINOR_RENDER ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fs_inode_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_destroy (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_ctxbitmap_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_destroy_members (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_remove_map_hash (struct drm_device*) ; 
 int /*<<< orphan*/  drm_minor_free (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_vblank_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

void drm_dev_fini(struct drm_device *dev)
{
	drm_vblank_cleanup(dev);

	if (drm_core_check_feature(dev, DRIVER_GEM))
		drm_gem_destroy(dev);

	drm_legacy_ctxbitmap_cleanup(dev);
	drm_legacy_remove_map_hash(dev);
	drm_fs_inode_free(dev->anon_inode);

	drm_minor_free(dev, DRM_MINOR_PRIMARY);
	drm_minor_free(dev, DRM_MINOR_RENDER);

	put_device(dev->dev);

	mutex_destroy(&dev->master_mutex);
	mutex_destroy(&dev->clientlist_mutex);
	mutex_destroy(&dev->filelist_mutex);
	mutex_destroy(&dev->struct_mutex);
	drm_legacy_destroy_members(dev);
	kfree(dev->unique);
}