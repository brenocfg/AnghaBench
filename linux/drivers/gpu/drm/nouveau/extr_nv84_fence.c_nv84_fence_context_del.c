#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nv84_fence_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  bo; } ;
struct TYPE_5__ {int /*<<< orphan*/  sequence; } ;
struct nv84_fence_chan {TYPE_2__ base; int /*<<< orphan*/  vma; } ;
struct nouveau_channel {int chid; struct nv84_fence_chan* fence; TYPE_1__* drm; } ;
struct TYPE_4__ {struct nv84_fence_priv* fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_bo_wr32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_fence_context_del (TYPE_2__*) ; 
 int /*<<< orphan*/  nouveau_fence_context_free (TYPE_2__*) ; 
 int /*<<< orphan*/  nouveau_vma_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv84_fence_context_del(struct nouveau_channel *chan)
{
	struct nv84_fence_priv *priv = chan->drm->fence;
	struct nv84_fence_chan *fctx = chan->fence;

	nouveau_bo_wr32(priv->bo, chan->chid * 16 / 4, fctx->base.sequence);
	mutex_lock(&priv->mutex);
	nouveau_vma_del(&fctx->vma);
	mutex_unlock(&priv->mutex);
	nouveau_fence_context_del(&fctx->base);
	chan->fence = NULL;
	nouveau_fence_context_free(&fctx->base);
}