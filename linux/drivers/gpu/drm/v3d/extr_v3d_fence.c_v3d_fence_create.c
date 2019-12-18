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
struct dma_fence {int dummy; } ;
struct v3d_fence {int queue; struct dma_fence base; scalar_t__ seqno; int /*<<< orphan*/ * dev; } ;
struct v3d_dev {TYPE_1__* queue; int /*<<< orphan*/  job_lock; int /*<<< orphan*/  drm; } ;
typedef  enum v3d_queue { ____Placeholder_v3d_queue } v3d_queue ;
struct TYPE_2__ {int /*<<< orphan*/  fence_context; scalar_t__ emit_seqno; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dma_fence* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_init (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct v3d_fence* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3d_fence_ops ; 

struct dma_fence *v3d_fence_create(struct v3d_dev *v3d, enum v3d_queue queue)
{
	struct v3d_fence *fence;

	fence = kzalloc(sizeof(*fence), GFP_KERNEL);
	if (!fence)
		return ERR_PTR(-ENOMEM);

	fence->dev = &v3d->drm;
	fence->queue = queue;
	fence->seqno = ++v3d->queue[queue].emit_seqno;
	dma_fence_init(&fence->base, &v3d_fence_ops, &v3d->job_lock,
		       v3d->queue[queue].fence_context, fence->seqno);

	return &fence->base;
}