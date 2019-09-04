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
struct TYPE_2__ {int /*<<< orphan*/  sync; int /*<<< orphan*/  read; int /*<<< orphan*/  emit; } ;
struct nv10_fence_chan {TYPE_1__ base; } ;
struct nouveau_channel {struct nv10_fence_chan* fence; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv10_fence_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_fence_context_new (struct nouveau_channel*,TYPE_1__*) ; 
 int /*<<< orphan*/  nv10_fence_emit ; 
 int /*<<< orphan*/  nv10_fence_read ; 
 int /*<<< orphan*/  nv10_fence_sync ; 

__attribute__((used)) static int
nv10_fence_context_new(struct nouveau_channel *chan)
{
	struct nv10_fence_chan *fctx;

	fctx = chan->fence = kzalloc(sizeof(*fctx), GFP_KERNEL);
	if (!fctx)
		return -ENOMEM;

	nouveau_fence_context_new(chan, &fctx->base);
	fctx->base.emit = nv10_fence_emit;
	fctx->base.read = nv10_fence_read;
	fctx->base.sync = nv10_fence_sync;
	return 0;
}