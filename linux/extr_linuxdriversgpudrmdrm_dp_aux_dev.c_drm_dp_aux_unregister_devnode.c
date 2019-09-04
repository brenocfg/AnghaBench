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
struct drm_dp_aux_dev {unsigned int index; int /*<<< orphan*/  refcount; scalar_t__ dev; int /*<<< orphan*/  usecount; } ;
struct drm_dp_aux {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aux_idr ; 
 int /*<<< orphan*/  aux_idr_mutex ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_major ; 
 int /*<<< orphan*/  drm_dp_aux_dev_class ; 
 struct drm_dp_aux_dev* drm_dp_aux_dev_get_by_aux (struct drm_dp_aux*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_drm_dp_aux_dev ; 
 int /*<<< orphan*/  wait_var_event (int /*<<< orphan*/ *,int) ; 

void drm_dp_aux_unregister_devnode(struct drm_dp_aux *aux)
{
	struct drm_dp_aux_dev *aux_dev;
	unsigned int minor;

	aux_dev = drm_dp_aux_dev_get_by_aux(aux);
	if (!aux_dev) /* attach must have failed */
		return;

	mutex_lock(&aux_idr_mutex);
	idr_remove(&aux_idr, aux_dev->index);
	mutex_unlock(&aux_idr_mutex);

	atomic_dec(&aux_dev->usecount);
	wait_var_event(&aux_dev->usecount, !atomic_read(&aux_dev->usecount));

	minor = aux_dev->index;
	if (aux_dev->dev)
		device_destroy(drm_dp_aux_dev_class,
			       MKDEV(drm_dev_major, minor));

	DRM_DEBUG("drm_dp_aux_dev: aux [%s] unregistering\n", aux->name);
	kref_put(&aux_dev->refcount, release_drm_dp_aux_dev);
}