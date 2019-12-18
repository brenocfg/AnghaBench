#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int /*<<< orphan*/  pid; int /*<<< orphan*/  event_list; int /*<<< orphan*/  prime; int /*<<< orphan*/  filp; TYPE_2__* minor; } ;
struct drm_device {TYPE_3__* driver; int /*<<< orphan*/  open_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* postclose ) (struct drm_device*,struct drm_file*) ;int /*<<< orphan*/  (* preclose ) (struct drm_device*,struct drm_file*) ;} ;
struct TYPE_5__ {TYPE_1__* kdev; struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_GEM ; 
 int /*<<< orphan*/  DRIVER_HAVE_DMA ; 
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRIVER_SYNCOBJ ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_events_release (struct drm_file*) ; 
 int /*<<< orphan*/  drm_fb_release (struct drm_file*) ; 
 int /*<<< orphan*/  drm_gem_release (struct drm_device*,struct drm_file*) ; 
 scalar_t__ drm_is_primary_client (struct drm_file*) ; 
 int /*<<< orphan*/  drm_legacy_ctxbitmap_flush (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  drm_legacy_lock_release (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_legacy_reclaim_buffers (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  drm_master_release (struct drm_file*) ; 
 int /*<<< orphan*/  drm_prime_destroy_file_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_property_destroy_user_blobs (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  drm_syncobj_release (struct drm_file*) ; 
 int /*<<< orphan*/  kfree (struct drm_file*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ old_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

void drm_file_free(struct drm_file *file)
{
	struct drm_device *dev;

	if (!file)
		return;

	dev = file->minor->dev;

	DRM_DEBUG("pid = %d, device = 0x%lx, open_count = %d\n",
		  task_pid_nr(current),
		  (long)old_encode_dev(file->minor->kdev->devt),
		  dev->open_count);

	if (drm_core_check_feature(dev, DRIVER_LEGACY) &&
	    dev->driver->preclose)
		dev->driver->preclose(dev, file);

	if (drm_core_check_feature(dev, DRIVER_LEGACY))
		drm_legacy_lock_release(dev, file->filp);

	if (drm_core_check_feature(dev, DRIVER_HAVE_DMA))
		drm_legacy_reclaim_buffers(dev, file);

	drm_events_release(file);

	if (drm_core_check_feature(dev, DRIVER_MODESET)) {
		drm_fb_release(file);
		drm_property_destroy_user_blobs(dev, file);
	}

	if (drm_core_check_feature(dev, DRIVER_SYNCOBJ))
		drm_syncobj_release(file);

	if (drm_core_check_feature(dev, DRIVER_GEM))
		drm_gem_release(dev, file);

	drm_legacy_ctxbitmap_flush(dev, file);

	if (drm_is_primary_client(file))
		drm_master_release(file);

	if (dev->driver->postclose)
		dev->driver->postclose(dev, file);

	drm_prime_destroy_file_private(&file->prime);

	WARN_ON(!list_empty(&file->event_list));

	put_pid(file->pid);
	kfree(file);
}