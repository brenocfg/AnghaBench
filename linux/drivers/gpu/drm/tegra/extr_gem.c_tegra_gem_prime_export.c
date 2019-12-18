#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct drm_gem_object {TYPE_4__* dev; int /*<<< orphan*/  size; } ;
struct dma_buf {int dummy; } ;
struct TYPE_10__ {TYPE_2__* driver; } ;
struct TYPE_9__ {int flags; struct drm_gem_object* priv; int /*<<< orphan*/  size; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; int /*<<< orphan*/  exp_name; } ;
struct TYPE_8__ {TYPE_1__* fops; } ;
struct TYPE_7__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_DMA_BUF_EXPORT_INFO (TYPE_3__) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 struct dma_buf* drm_gem_dmabuf_export (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__ exp_info ; 
 int /*<<< orphan*/  tegra_gem_prime_dmabuf_ops ; 

struct dma_buf *tegra_gem_prime_export(struct drm_gem_object *gem,
				       int flags)
{
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);

	exp_info.exp_name = KBUILD_MODNAME;
	exp_info.owner = gem->dev->driver->fops->owner;
	exp_info.ops = &tegra_gem_prime_dmabuf_ops;
	exp_info.size = gem->size;
	exp_info.flags = flags;
	exp_info.priv = gem;

	return drm_gem_dmabuf_export(gem->dev, &exp_info);
}