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
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  ctxlist_mutex; int /*<<< orphan*/  ctxlist; } ;
struct drm_ctx_list {int handle; int /*<<< orphan*/  head; struct drm_file* tag; } ;
struct drm_ctx {int handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_KMS_LEGACY_CONTEXT ; 
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int DRM_KERNEL_CONTEXT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_legacy_ctxbitmap_next (struct drm_device*) ; 
 struct drm_ctx_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_legacy_addctx(struct drm_device *dev, void *data,
		      struct drm_file *file_priv)
{
	struct drm_ctx_list *ctx_entry;
	struct drm_ctx *ctx = data;
	int tmp_handle;

	if (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		return -EOPNOTSUPP;

	tmp_handle = drm_legacy_ctxbitmap_next(dev);
	if (tmp_handle == DRM_KERNEL_CONTEXT) {
		/* Skip kernel's context and get a new one. */
		tmp_handle = drm_legacy_ctxbitmap_next(dev);
	}
	DRM_DEBUG("%d\n", tmp_handle);
	if (tmp_handle < 0) {
		DRM_DEBUG("Not enough free contexts.\n");
		/* Should this return -EBUSY instead? */
		return tmp_handle;
	}

	ctx->handle = tmp_handle;

	ctx_entry = kmalloc(sizeof(*ctx_entry), GFP_KERNEL);
	if (!ctx_entry) {
		DRM_DEBUG("out of memory\n");
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&ctx_entry->head);
	ctx_entry->handle = ctx->handle;
	ctx_entry->tag = file_priv;

	mutex_lock(&dev->ctxlist_mutex);
	list_add(&ctx_entry->head, &dev->ctxlist);
	mutex_unlock(&dev->ctxlist_mutex);

	return 0;
}