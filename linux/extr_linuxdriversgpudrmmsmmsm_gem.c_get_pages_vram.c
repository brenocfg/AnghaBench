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
struct page {int dummy; } ;
struct msm_gem_object {int /*<<< orphan*/  vram_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;
struct msm_drm_private {TYPE_2__ vram; } ;
struct drm_gem_object {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct page** ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 int drm_mm_insert_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 
 struct page** kvmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct page* phys_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physaddr (struct drm_gem_object*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

__attribute__((used)) static struct page **get_pages_vram(struct drm_gem_object *obj, int npages)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	struct msm_drm_private *priv = obj->dev->dev_private;
	dma_addr_t paddr;
	struct page **p;
	int ret, i;

	p = kvmalloc_array(npages, sizeof(struct page *), GFP_KERNEL);
	if (!p)
		return ERR_PTR(-ENOMEM);

	spin_lock(&priv->vram.lock);
	ret = drm_mm_insert_node(&priv->vram.mm, msm_obj->vram_node, npages);
	spin_unlock(&priv->vram.lock);
	if (ret) {
		kvfree(p);
		return ERR_PTR(ret);
	}

	paddr = physaddr(obj);
	for (i = 0; i < npages; i++) {
		p[i] = phys_to_page(paddr);
		paddr += PAGE_SIZE;
	}

	return p;
}