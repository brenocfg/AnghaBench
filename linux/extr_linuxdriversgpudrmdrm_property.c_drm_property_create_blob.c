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
struct drm_property_blob {size_t length; int /*<<< orphan*/  head_global; int /*<<< orphan*/  base; void* data; struct drm_device* dev; int /*<<< orphan*/  head_file; } ;
struct TYPE_2__ {int /*<<< orphan*/  blob_lock; int /*<<< orphan*/  property_blob_list; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_OBJECT_BLOB ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct drm_property_blob* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ULONG_MAX ; 
 int __drm_mode_object_add (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_property_free_blob ; 
 int /*<<< orphan*/  kvfree (struct drm_property_blob*) ; 
 struct drm_property_blob* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct drm_property_blob *
drm_property_create_blob(struct drm_device *dev, size_t length,
			 const void *data)
{
	struct drm_property_blob *blob;
	int ret;

	if (!length || length > ULONG_MAX - sizeof(struct drm_property_blob))
		return ERR_PTR(-EINVAL);

	blob = kvzalloc(sizeof(struct drm_property_blob)+length, GFP_KERNEL);
	if (!blob)
		return ERR_PTR(-ENOMEM);

	/* This must be explicitly initialised, so we can safely call list_del
	 * on it in the removal handler, even if it isn't in a file list. */
	INIT_LIST_HEAD(&blob->head_file);
	blob->data = (void *)blob + sizeof(*blob);
	blob->length = length;
	blob->dev = dev;

	if (data)
		memcpy(blob->data, data, length);

	ret = __drm_mode_object_add(dev, &blob->base, DRM_MODE_OBJECT_BLOB,
				    true, drm_property_free_blob);
	if (ret) {
		kvfree(blob);
		return ERR_PTR(-EINVAL);
	}

	mutex_lock(&dev->mode_config.blob_lock);
	list_add_tail(&blob->head_global,
	              &dev->mode_config.property_blob_list);
	mutex_unlock(&dev->mode_config.blob_lock);

	return blob;
}