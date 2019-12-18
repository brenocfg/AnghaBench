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
struct drm_driver {int dummy; } ;
struct drm_device {unsigned int driver_features; int /*<<< orphan*/  struct_mutex; int /*<<< orphan*/  filelist_mutex; int /*<<< orphan*/  clientlist_mutex; int /*<<< orphan*/  master_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  anon_inode; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  vblank_event_list; int /*<<< orphan*/  clientlist; int /*<<< orphan*/  filelist_internal; int /*<<< orphan*/  filelist; struct drm_driver* driver; int /*<<< orphan*/  ref; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRIVER_GEM ; 
 int /*<<< orphan*/  DRIVER_RENDER ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_MINOR_PRIMARY ; 
 int /*<<< orphan*/  DRM_MINOR_RENDER ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_init_complete ; 
 int drm_dev_set_unique (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fs_inode_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fs_inode_new () ; 
 int /*<<< orphan*/  drm_gem_destroy (struct drm_device*) ; 
 int drm_gem_init (struct drm_device*) ; 
 int drm_legacy_create_map_hash (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_ctxbitmap_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_ctxbitmap_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_destroy_members (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_init_members (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_remove_map_hash (struct drm_device*) ; 
 int drm_minor_alloc (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_minor_free (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int drm_dev_init(struct drm_device *dev,
		 struct drm_driver *driver,
		 struct device *parent)
{
	int ret;

	if (!drm_core_init_complete) {
		DRM_ERROR("DRM core is not initialized\n");
		return -ENODEV;
	}

	BUG_ON(!parent);

	kref_init(&dev->ref);
	dev->dev = get_device(parent);
	dev->driver = driver;

	/* no per-device feature limits by default */
	dev->driver_features = ~0u;

	drm_legacy_init_members(dev);
	INIT_LIST_HEAD(&dev->filelist);
	INIT_LIST_HEAD(&dev->filelist_internal);
	INIT_LIST_HEAD(&dev->clientlist);
	INIT_LIST_HEAD(&dev->vblank_event_list);

	spin_lock_init(&dev->event_lock);
	mutex_init(&dev->struct_mutex);
	mutex_init(&dev->filelist_mutex);
	mutex_init(&dev->clientlist_mutex);
	mutex_init(&dev->master_mutex);

	dev->anon_inode = drm_fs_inode_new();
	if (IS_ERR(dev->anon_inode)) {
		ret = PTR_ERR(dev->anon_inode);
		DRM_ERROR("Cannot allocate anonymous inode: %d\n", ret);
		goto err_free;
	}

	if (drm_core_check_feature(dev, DRIVER_RENDER)) {
		ret = drm_minor_alloc(dev, DRM_MINOR_RENDER);
		if (ret)
			goto err_minors;
	}

	ret = drm_minor_alloc(dev, DRM_MINOR_PRIMARY);
	if (ret)
		goto err_minors;

	ret = drm_legacy_create_map_hash(dev);
	if (ret)
		goto err_minors;

	drm_legacy_ctxbitmap_init(dev);

	if (drm_core_check_feature(dev, DRIVER_GEM)) {
		ret = drm_gem_init(dev);
		if (ret) {
			DRM_ERROR("Cannot initialize graphics execution manager (GEM)\n");
			goto err_ctxbitmap;
		}
	}

	ret = drm_dev_set_unique(dev, dev_name(parent));
	if (ret)
		goto err_setunique;

	return 0;

err_setunique:
	if (drm_core_check_feature(dev, DRIVER_GEM))
		drm_gem_destroy(dev);
err_ctxbitmap:
	drm_legacy_ctxbitmap_cleanup(dev);
	drm_legacy_remove_map_hash(dev);
err_minors:
	drm_minor_free(dev, DRM_MINOR_PRIMARY);
	drm_minor_free(dev, DRM_MINOR_RENDER);
	drm_fs_inode_free(dev->anon_inode);
err_free:
	put_device(dev->dev);
	mutex_destroy(&dev->master_mutex);
	mutex_destroy(&dev->clientlist_mutex);
	mutex_destroy(&dev->filelist_mutex);
	mutex_destroy(&dev->struct_mutex);
	drm_legacy_destroy_members(dev);
	return ret;
}