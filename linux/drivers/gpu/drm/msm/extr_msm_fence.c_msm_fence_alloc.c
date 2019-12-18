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
struct msm_fence_context {int /*<<< orphan*/  last_fence; int /*<<< orphan*/  context; int /*<<< orphan*/  spinlock; } ;
struct dma_fence {int dummy; } ;
struct msm_fence {struct dma_fence base; struct msm_fence_context* fctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dma_fence* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_init (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msm_fence* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_fence_ops ; 

struct dma_fence *
msm_fence_alloc(struct msm_fence_context *fctx)
{
	struct msm_fence *f;

	f = kzalloc(sizeof(*f), GFP_KERNEL);
	if (!f)
		return ERR_PTR(-ENOMEM);

	f->fctx = fctx;

	dma_fence_init(&f->base, &msm_fence_ops, &fctx->spinlock,
		       fctx->context, ++fctx->last_fence);

	return &f->base;
}