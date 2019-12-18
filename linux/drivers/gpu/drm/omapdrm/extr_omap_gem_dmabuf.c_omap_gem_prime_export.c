#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_object {int /*<<< orphan*/  dev; int /*<<< orphan*/  size; } ;
struct dma_buf {int dummy; } ;
struct TYPE_4__ {int flags; struct drm_gem_object* priv; int /*<<< orphan*/  size; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_DMA_BUF_EXPORT_INFO (TYPE_1__) ; 
 struct dma_buf* drm_gem_dmabuf_export (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ exp_info ; 
 int /*<<< orphan*/  omap_dmabuf_ops ; 

struct dma_buf *omap_gem_prime_export(struct drm_gem_object *obj, int flags)
{
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.ops = &omap_dmabuf_ops;
	exp_info.size = obj->size;
	exp_info.flags = flags;
	exp_info.priv = obj;

	return drm_gem_dmabuf_export(obj->dev, &exp_info);
}