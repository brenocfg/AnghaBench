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
struct sg_table {int /*<<< orphan*/  sgl; } ;
struct TYPE_2__ {int /*<<< orphan*/  import_attach; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ IS_ERR (struct sg_table*) ; 
 int PTR_ERR (struct sg_table*) ; 
 int /*<<< orphan*/  __i915_gem_object_set_pages (struct drm_i915_gem_object*,struct sg_table*,unsigned int) ; 
 struct sg_table* dma_buf_map_attachment (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int i915_sg_page_sizes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_gem_object_get_pages_dmabuf(struct drm_i915_gem_object *obj)
{
	struct sg_table *pages;
	unsigned int sg_page_sizes;

	pages = dma_buf_map_attachment(obj->base.import_attach,
				       DMA_BIDIRECTIONAL);
	if (IS_ERR(pages))
		return PTR_ERR(pages);

	sg_page_sizes = i915_sg_page_sizes(pages->sgl);

	__i915_gem_object_set_pages(obj, pages, sg_page_sizes);

	return 0;
}