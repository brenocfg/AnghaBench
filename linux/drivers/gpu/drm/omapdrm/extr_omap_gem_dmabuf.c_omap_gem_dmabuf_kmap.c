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
struct page {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct dma_buf {struct drm_gem_object* priv; } ;

/* Variables and functions */
 void* kmap (struct page*) ; 
 int /*<<< orphan*/  omap_gem_cpu_sync_page (struct drm_gem_object*,unsigned long) ; 
 int /*<<< orphan*/  omap_gem_get_pages (struct drm_gem_object*,struct page***,int) ; 

__attribute__((used)) static void *omap_gem_dmabuf_kmap(struct dma_buf *buffer,
		unsigned long page_num)
{
	struct drm_gem_object *obj = buffer->priv;
	struct page **pages;
	omap_gem_get_pages(obj, &pages, false);
	omap_gem_cpu_sync_page(obj, page_num);
	return kmap(pages[page_num]);
}