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
struct mtk_drm_gem_obj {int /*<<< orphan*/  base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 struct mtk_drm_gem_obj* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct mtk_drm_gem_obj*) ; 
 struct mtk_drm_gem_obj* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned long round_up (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mtk_drm_gem_obj *mtk_drm_gem_init(struct drm_device *dev,
						unsigned long size)
{
	struct mtk_drm_gem_obj *mtk_gem_obj;
	int ret;

	size = round_up(size, PAGE_SIZE);

	mtk_gem_obj = kzalloc(sizeof(*mtk_gem_obj), GFP_KERNEL);
	if (!mtk_gem_obj)
		return ERR_PTR(-ENOMEM);

	ret = drm_gem_object_init(dev, &mtk_gem_obj->base, size);
	if (ret < 0) {
		DRM_ERROR("failed to initialize gem object\n");
		kfree(mtk_gem_obj);
		return ERR_PTR(ret);
	}

	return mtk_gem_obj;
}