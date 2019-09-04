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
struct ucma_file {int /*<<< orphan*/  ctx_list; } ;
struct ucma_context {scalar_t__ id; int /*<<< orphan*/  list; struct ucma_file* file; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  comp; int /*<<< orphan*/  ref; int /*<<< orphan*/  close_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ctx_idr ; 
 scalar_t__ idr_alloc (int /*<<< orphan*/ *,struct ucma_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ucma_context*) ; 
 struct ucma_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucma_close_id ; 

__attribute__((used)) static struct ucma_context *ucma_alloc_ctx(struct ucma_file *file)
{
	struct ucma_context *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return NULL;

	INIT_WORK(&ctx->close_work, ucma_close_id);
	atomic_set(&ctx->ref, 1);
	init_completion(&ctx->comp);
	INIT_LIST_HEAD(&ctx->mc_list);
	ctx->file = file;

	mutex_lock(&mut);
	ctx->id = idr_alloc(&ctx_idr, ctx, 0, 0, GFP_KERNEL);
	mutex_unlock(&mut);
	if (ctx->id < 0)
		goto error;

	list_add_tail(&ctx->list, &file->ctx_list);
	return ctx;

error:
	kfree(ctx);
	return NULL;
}