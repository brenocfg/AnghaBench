#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nouveau_fence_chan {scalar_t__ (* sync ) (struct nouveau_fence*,struct nouveau_channel*,struct nouveau_channel*) ;} ;
struct nouveau_fence {int /*<<< orphan*/  channel; } ;
struct nouveau_channel {int /*<<< orphan*/  drm; struct nouveau_fence_chan* fence; } ;
struct TYPE_3__ {struct dma_resv* resv; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct nouveau_bo {TYPE_2__ bo; } ;
struct dma_resv_list {int shared_count; int /*<<< orphan*/ * shared; } ;
struct dma_resv {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int dma_fence_wait (struct dma_fence*,int) ; 
 struct dma_fence* dma_resv_get_excl (struct dma_resv*) ; 
 struct dma_resv_list* dma_resv_get_list (struct dma_resv*) ; 
 int /*<<< orphan*/  dma_resv_held (struct dma_resv*) ; 
 int dma_resv_reserve_shared (struct dma_resv*,int) ; 
 struct nouveau_fence* nouveau_local_fence (struct dma_fence*,int /*<<< orphan*/ ) ; 
 struct nouveau_channel* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ stub1 (struct nouveau_fence*,struct nouveau_channel*,struct nouveau_channel*) ; 
 scalar_t__ stub2 (struct nouveau_fence*,struct nouveau_channel*,struct nouveau_channel*) ; 

int
nouveau_fence_sync(struct nouveau_bo *nvbo, struct nouveau_channel *chan, bool exclusive, bool intr)
{
	struct nouveau_fence_chan *fctx = chan->fence;
	struct dma_fence *fence;
	struct dma_resv *resv = nvbo->bo.base.resv;
	struct dma_resv_list *fobj;
	struct nouveau_fence *f;
	int ret = 0, i;

	if (!exclusive) {
		ret = dma_resv_reserve_shared(resv, 1);

		if (ret)
			return ret;
	}

	fobj = dma_resv_get_list(resv);
	fence = dma_resv_get_excl(resv);

	if (fence && (!exclusive || !fobj || !fobj->shared_count)) {
		struct nouveau_channel *prev = NULL;
		bool must_wait = true;

		f = nouveau_local_fence(fence, chan->drm);
		if (f) {
			rcu_read_lock();
			prev = rcu_dereference(f->channel);
			if (prev && (prev == chan || fctx->sync(f, prev, chan) == 0))
				must_wait = false;
			rcu_read_unlock();
		}

		if (must_wait)
			ret = dma_fence_wait(fence, intr);

		return ret;
	}

	if (!exclusive || !fobj)
		return ret;

	for (i = 0; i < fobj->shared_count && !ret; ++i) {
		struct nouveau_channel *prev = NULL;
		bool must_wait = true;

		fence = rcu_dereference_protected(fobj->shared[i],
						dma_resv_held(resv));

		f = nouveau_local_fence(fence, chan->drm);
		if (f) {
			rcu_read_lock();
			prev = rcu_dereference(f->channel);
			if (prev && (prev == chan || fctx->sync(f, prev, chan) == 0))
				must_wait = false;
			rcu_read_unlock();
		}

		if (must_wait)
			ret = dma_fence_wait(fence, intr);
	}

	return ret;
}