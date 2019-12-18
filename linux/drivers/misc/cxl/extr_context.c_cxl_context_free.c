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
struct cxl_context {int /*<<< orphan*/  rcu; TYPE_1__* afu; int /*<<< orphan*/  pe; scalar_t__ mapping; scalar_t__ kernelapi; } ;
struct TYPE_2__ {int /*<<< orphan*/  contexts_lock; int /*<<< orphan*/  contexts_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_release_mapping (struct cxl_context*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reclaim_ctx ; 

void cxl_context_free(struct cxl_context *ctx)
{
	if (ctx->kernelapi && ctx->mapping)
		cxl_release_mapping(ctx);
	mutex_lock(&ctx->afu->contexts_lock);
	idr_remove(&ctx->afu->contexts_idr, ctx->pe);
	mutex_unlock(&ctx->afu->contexts_lock);
	call_rcu(&ctx->rcu, reclaim_ctx);
}