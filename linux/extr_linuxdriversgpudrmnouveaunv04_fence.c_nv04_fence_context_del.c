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
struct nv04_fence_chan {int /*<<< orphan*/  base; } ;
struct nouveau_channel {struct nv04_fence_chan* fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_fence_context_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_fence_context_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv04_fence_context_del(struct nouveau_channel *chan)
{
	struct nv04_fence_chan *fctx = chan->fence;
	nouveau_fence_context_del(&fctx->base);
	chan->fence = NULL;
	nouveau_fence_context_free(&fctx->base);
}