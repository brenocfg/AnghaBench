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
struct nouveau_fence_chan {int /*<<< orphan*/  fence_ref; } ;
struct nouveau_fence {int /*<<< orphan*/  base; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_free (int /*<<< orphan*/ *) ; 
 struct nouveau_fence* from_fence (struct dma_fence*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nouveau_fence_chan* nouveau_fctx (struct nouveau_fence*) ; 
 int /*<<< orphan*/  nouveau_fence_context_put ; 

__attribute__((used)) static void nouveau_fence_release(struct dma_fence *f)
{
	struct nouveau_fence *fence = from_fence(f);
	struct nouveau_fence_chan *fctx = nouveau_fctx(fence);

	kref_put(&fctx->fence_ref, nouveau_fence_context_put);
	dma_fence_free(&fence->base);
}