#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct drm_property_blob {int /*<<< orphan*/  head_file; TYPE_1__ base; int /*<<< orphan*/  data; } ;
struct drm_mode_create_blob {int /*<<< orphan*/  blob_id; int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct drm_file {int /*<<< orphan*/  blobs; } ;
struct TYPE_4__ {int /*<<< orphan*/  blob_lock; } ;
struct drm_device {TYPE_2__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int EFAULT ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct drm_property_blob*) ; 
 int PTR_ERR (struct drm_property_blob*) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_blob_put (struct drm_property_blob*) ; 
 struct drm_property_blob* drm_property_create_blob (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

int drm_mode_createblob_ioctl(struct drm_device *dev,
			      void *data, struct drm_file *file_priv)
{
	struct drm_mode_create_blob *out_resp = data;
	struct drm_property_blob *blob;
	int ret = 0;

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		return -EOPNOTSUPP;

	blob = drm_property_create_blob(dev, out_resp->length, NULL);
	if (IS_ERR(blob))
		return PTR_ERR(blob);

	if (copy_from_user(blob->data,
			   u64_to_user_ptr(out_resp->data),
			   out_resp->length)) {
		ret = -EFAULT;
		goto out_blob;
	}

	/* Dropping the lock between create_blob and our access here is safe
	 * as only the same file_priv can remove the blob; at this point, it is
	 * not associated with any file_priv. */
	mutex_lock(&dev->mode_config.blob_lock);
	out_resp->blob_id = blob->base.id;
	list_add_tail(&blob->head_file, &file_priv->blobs);
	mutex_unlock(&dev->mode_config.blob_lock);

	return 0;

out_blob:
	drm_property_blob_put(blob);
	return ret;
}