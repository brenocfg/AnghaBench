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
struct mtk_drm_private {int /*<<< orphan*/  dma_dev; } ;
struct mtk_drm_gem_obj {int /*<<< orphan*/  dma_attrs; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cookie; scalar_t__ sg; } ;
struct drm_gem_object {int /*<<< orphan*/  size; TYPE_1__* dev; } ;
struct TYPE_2__ {struct mtk_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct mtk_drm_gem_obj*) ; 
 struct mtk_drm_gem_obj* to_mtk_gem_obj (struct drm_gem_object*) ; 

void mtk_drm_gem_free_object(struct drm_gem_object *obj)
{
	struct mtk_drm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	struct mtk_drm_private *priv = obj->dev->dev_private;

	if (mtk_gem->sg)
		drm_prime_gem_destroy(obj, mtk_gem->sg);
	else
		dma_free_attrs(priv->dma_dev, obj->size, mtk_gem->cookie,
			       mtk_gem->dma_addr, mtk_gem->dma_attrs);

	/* release file pointer to gem object. */
	drm_gem_object_release(obj);

	kfree(mtk_gem);
}