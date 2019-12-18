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
struct nouveau_fence {int dummy; } ;
struct TYPE_2__ {scalar_t__ context_base; scalar_t__ nr; } ;
struct nouveau_drm {TYPE_1__ chan; } ;
struct dma_fence {scalar_t__ context; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 struct nouveau_fence* from_fence (struct dma_fence*) ; 
 int /*<<< orphan*/  nouveau_fence_ops_legacy ; 
 int /*<<< orphan*/  nouveau_fence_ops_uevent ; 

__attribute__((used)) static struct nouveau_fence *
nouveau_local_fence(struct dma_fence *fence, struct nouveau_drm *drm)
{
	if (fence->ops != &nouveau_fence_ops_legacy &&
	    fence->ops != &nouveau_fence_ops_uevent)
		return NULL;

	if (fence->context < drm->chan.context_base ||
	    fence->context >= drm->chan.context_base + drm->chan.nr)
		return NULL;

	return from_fence(fence);
}