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
struct drm_global_reference {int size; int /*<<< orphan*/ * release; int /*<<< orphan*/ * init; int /*<<< orphan*/  global_type; int /*<<< orphan*/  object; } ;
struct TYPE_2__ {struct drm_global_reference ref; int /*<<< orphan*/  mem_glob; } ;
struct vmw_private {struct drm_global_reference mem_global_ref; TYPE_1__ bo_global_ref; } ;
struct ttm_mem_global {int dummy; } ;
struct ttm_bo_global {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_GLOBAL_TTM_BO ; 
 int /*<<< orphan*/  DRM_GLOBAL_TTM_MEM ; 
 int drm_global_item_ref (struct drm_global_reference*) ; 
 int /*<<< orphan*/  drm_global_item_unref (struct drm_global_reference*) ; 
 int /*<<< orphan*/  ttm_bo_global_init ; 
 int /*<<< orphan*/  ttm_bo_global_release ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_ttm_mem_global_init ; 
 int /*<<< orphan*/  vmw_ttm_mem_global_release ; 

int vmw_ttm_global_init(struct vmw_private *dev_priv)
{
	struct drm_global_reference *global_ref;
	int ret;

	global_ref = &dev_priv->mem_global_ref;
	global_ref->global_type = DRM_GLOBAL_TTM_MEM;
	global_ref->size = sizeof(struct ttm_mem_global);
	global_ref->init = &vmw_ttm_mem_global_init;
	global_ref->release = &vmw_ttm_mem_global_release;

	ret = drm_global_item_ref(global_ref);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed setting up TTM memory accounting.\n");
		return ret;
	}

	dev_priv->bo_global_ref.mem_glob =
		dev_priv->mem_global_ref.object;
	global_ref = &dev_priv->bo_global_ref.ref;
	global_ref->global_type = DRM_GLOBAL_TTM_BO;
	global_ref->size = sizeof(struct ttm_bo_global);
	global_ref->init = &ttm_bo_global_init;
	global_ref->release = &ttm_bo_global_release;
	ret = drm_global_item_ref(global_ref);

	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed setting up TTM buffer objects.\n");
		goto out_no_bo;
	}

	return 0;
out_no_bo:
	drm_global_item_unref(&dev_priv->mem_global_ref);
	return ret;
}