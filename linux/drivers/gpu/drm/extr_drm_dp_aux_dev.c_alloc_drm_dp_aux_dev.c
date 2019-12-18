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
struct drm_dp_aux_dev {int index; int /*<<< orphan*/  refcount; int /*<<< orphan*/  usecount; struct drm_dp_aux* aux; } ;
struct drm_dp_aux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_AUX_MINORS ; 
 int ENOMEM ; 
 struct drm_dp_aux_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  aux_idr ; 
 int /*<<< orphan*/  aux_idr_mutex ; 
 int idr_alloc (int /*<<< orphan*/ *,struct drm_dp_aux_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_dp_aux_dev*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct drm_dp_aux_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_dp_aux_dev *alloc_drm_dp_aux_dev(struct drm_dp_aux *aux)
{
	struct drm_dp_aux_dev *aux_dev;
	int index;

	aux_dev = kzalloc(sizeof(*aux_dev), GFP_KERNEL);
	if (!aux_dev)
		return ERR_PTR(-ENOMEM);
	aux_dev->aux = aux;
	atomic_set(&aux_dev->usecount, 1);
	kref_init(&aux_dev->refcount);

	mutex_lock(&aux_idr_mutex);
	index = idr_alloc(&aux_idr, aux_dev, 0, DRM_AUX_MINORS, GFP_KERNEL);
	mutex_unlock(&aux_idr_mutex);
	if (index < 0) {
		kfree(aux_dev);
		return ERR_PTR(index);
	}
	aux_dev->index = index;

	return aux_dev;
}