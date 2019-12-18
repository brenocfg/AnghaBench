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
struct drm_gem_object {int dummy; } ;
struct dma_buf {struct drm_gem_object* priv; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 void* drm_gem_vmap (struct drm_gem_object*) ; 

void *drm_gem_dmabuf_vmap(struct dma_buf *dma_buf)
{
	struct drm_gem_object *obj = dma_buf->priv;
	void *vaddr;

	vaddr = drm_gem_vmap(obj);
	if (IS_ERR(vaddr))
		vaddr = NULL;

	return vaddr;
}