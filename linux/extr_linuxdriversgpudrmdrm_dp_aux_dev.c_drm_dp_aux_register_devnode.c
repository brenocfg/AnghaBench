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
struct drm_dp_aux_dev {int /*<<< orphan*/  index; struct drm_dp_aux_dev* dev; } ;
struct drm_dp_aux {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct drm_dp_aux_dev*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct drm_dp_aux_dev*) ; 
 struct drm_dp_aux_dev* alloc_drm_dp_aux_dev (struct drm_dp_aux*) ; 
 struct drm_dp_aux_dev* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_major ; 
 int /*<<< orphan*/  drm_dp_aux_dev_class ; 
 int /*<<< orphan*/  drm_dp_aux_unregister_devnode (struct drm_dp_aux*) ; 

int drm_dp_aux_register_devnode(struct drm_dp_aux *aux)
{
	struct drm_dp_aux_dev *aux_dev;
	int res;

	aux_dev = alloc_drm_dp_aux_dev(aux);
	if (IS_ERR(aux_dev))
		return PTR_ERR(aux_dev);

	aux_dev->dev = device_create(drm_dp_aux_dev_class, aux->dev,
				     MKDEV(drm_dev_major, aux_dev->index), NULL,
				     "drm_dp_aux%d", aux_dev->index);
	if (IS_ERR(aux_dev->dev)) {
		res = PTR_ERR(aux_dev->dev);
		aux_dev->dev = NULL;
		goto error;
	}

	DRM_DEBUG("drm_dp_aux_dev: aux [%s] registered as minor %d\n",
		  aux->name, aux_dev->index);
	return 0;
error:
	drm_dp_aux_unregister_devnode(aux);
	return res;
}