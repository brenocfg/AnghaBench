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
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct sis_memblock {TYPE_1__ req; int /*<<< orphan*/  mm_node; int /*<<< orphan*/  owner_list; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; TYPE_2__* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  object_idr; } ;
typedef  TYPE_2__ drm_sis_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  free; } ;
typedef  TYPE_3__ drm_sis_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ drm_mm_node_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 struct sis_memblock* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sis_memblock*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sis_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sis_drm_free(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_sis_private_t *dev_priv = dev->dev_private;
	drm_sis_mem_t *mem = data;
	struct sis_memblock *obj;

	mutex_lock(&dev->struct_mutex);
	obj = idr_find(&dev_priv->object_idr, mem->free);
	if (obj == NULL) {
		mutex_unlock(&dev->struct_mutex);
		return -EINVAL;
	}

	idr_remove(&dev_priv->object_idr, mem->free);
	list_del(&obj->owner_list);
	if (drm_mm_node_allocated(&obj->mm_node))
		drm_mm_remove_node(&obj->mm_node);
#if defined(CONFIG_FB_SIS) || defined(CONFIG_FB_SIS_MODULE)
	else
		sis_free(obj->req.offset);
#endif
	kfree(obj);
	mutex_unlock(&dev->struct_mutex);
	DRM_DEBUG("free = 0x%lx\n", mem->free);

	return 0;
}