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
struct sg_table {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {struct drm_gem_object* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 int /*<<< orphan*/  omap_gem_unpin (struct drm_gem_object*) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 

__attribute__((used)) static void omap_gem_unmap_dma_buf(struct dma_buf_attachment *attachment,
		struct sg_table *sg, enum dma_data_direction dir)
{
	struct drm_gem_object *obj = attachment->dmabuf->priv;
	omap_gem_unpin(obj);
	sg_free_table(sg);
	kfree(sg);
}