#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct drm_file {int dummy; } ;
struct drm_device_dma {size_t buf_count; int /*<<< orphan*/ * buflist; } ;
struct drm_device {scalar_t__ dev_private; struct drm_device_dma* dma; } ;
struct TYPE_4__ {size_t idx; int /*<<< orphan*/  used; int /*<<< orphan*/  discard; } ;
typedef  TYPE_1__ drm_i810_vertex_t ;
struct TYPE_5__ {int last_dispatch; scalar_t__ last_enqueue; } ;
typedef  TYPE_2__ drm_i810_sarea_t ;
struct TYPE_6__ {scalar_t__ counter; scalar_t__ sarea_priv; scalar_t__* hw_status_page; } ;
typedef  TYPE_3__ drm_i810_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  i810_dma_dispatch_vertex (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i810_dma_vertex(struct drm_device *dev, void *data,
			   struct drm_file *file_priv)
{
	struct drm_device_dma *dma = dev->dma;
	drm_i810_private_t *dev_priv = (drm_i810_private_t *) dev->dev_private;
	u32 *hw_status = dev_priv->hw_status_page;
	drm_i810_sarea_t *sarea_priv = (drm_i810_sarea_t *)
	    dev_priv->sarea_priv;
	drm_i810_vertex_t *vertex = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DRM_DEBUG("idx %d used %d discard %d\n",
		  vertex->idx, vertex->used, vertex->discard);

	if (vertex->idx < 0 || vertex->idx >= dma->buf_count)
		return -EINVAL;

	i810_dma_dispatch_vertex(dev,
				 dma->buflist[vertex->idx],
				 vertex->discard, vertex->used);

	sarea_priv->last_enqueue = dev_priv->counter - 1;
	sarea_priv->last_dispatch = (int)hw_status[5];

	return 0;
}