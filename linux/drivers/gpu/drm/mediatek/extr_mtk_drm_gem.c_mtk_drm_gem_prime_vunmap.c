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
struct mtk_drm_gem_obj {scalar_t__ pages; scalar_t__ kvaddr; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 
 struct mtk_drm_gem_obj* to_mtk_gem_obj (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

void mtk_drm_gem_prime_vunmap(struct drm_gem_object *obj, void *vaddr)
{
	struct mtk_drm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);

	if (!mtk_gem->pages)
		return;

	vunmap(vaddr);
	mtk_gem->kvaddr = 0;
	kfree((void *)mtk_gem->pages);
}