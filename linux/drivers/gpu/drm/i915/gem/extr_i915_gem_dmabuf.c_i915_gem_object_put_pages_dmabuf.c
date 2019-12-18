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
struct TYPE_2__ {int /*<<< orphan*/  import_attach; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_buf_unmap_attachment (int /*<<< orphan*/ ,struct sg_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i915_gem_object_put_pages_dmabuf(struct drm_i915_gem_object *obj,
					     struct sg_table *pages)
{
	dma_buf_unmap_attachment(obj->base.import_attach, pages,
				 DMA_BIDIRECTIONAL);
}