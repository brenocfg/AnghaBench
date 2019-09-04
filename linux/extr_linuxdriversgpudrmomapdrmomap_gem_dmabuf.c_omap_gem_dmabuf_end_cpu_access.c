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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  omap_gem_put_pages (struct drm_gem_object*) ; 

__attribute__((used)) static int omap_gem_dmabuf_end_cpu_access(struct dma_buf *buffer,
					  enum dma_data_direction dir)
{
	struct drm_gem_object *obj = buffer->priv;
	omap_gem_put_pages(obj);
	return 0;
}