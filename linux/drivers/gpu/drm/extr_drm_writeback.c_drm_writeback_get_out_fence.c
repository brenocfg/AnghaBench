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
struct TYPE_2__ {scalar_t__ connector_type; } ;
struct drm_writeback_connector {int /*<<< orphan*/  fence_seqno; int /*<<< orphan*/  fence_context; int /*<<< orphan*/  fence_lock; TYPE_1__ base; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTOR_WRITEBACK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dma_fence_init (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_writeback_fence_ops ; 
 struct dma_fence* kzalloc (int,int /*<<< orphan*/ ) ; 

struct dma_fence *
drm_writeback_get_out_fence(struct drm_writeback_connector *wb_connector)
{
	struct dma_fence *fence;

	if (WARN_ON(wb_connector->base.connector_type !=
		    DRM_MODE_CONNECTOR_WRITEBACK))
		return NULL;

	fence = kzalloc(sizeof(*fence), GFP_KERNEL);
	if (!fence)
		return NULL;

	dma_fence_init(fence, &drm_writeback_fence_ops,
		       &wb_connector->fence_lock, wb_connector->fence_context,
		       ++wb_connector->fence_seqno);

	return fence;
}