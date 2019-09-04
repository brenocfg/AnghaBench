#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  robj; } ;
struct amdgpu_cs_parser {unsigned int num_post_dep_syncobjs; unsigned int nchunks; TYPE_1__ uf_entry; scalar_t__ job; TYPE_2__* chunks; scalar_t__ bo_list; TYPE_4__* ctx; int /*<<< orphan*/  fence; TYPE_2__* post_dep_syncobjs; int /*<<< orphan*/  validated; int /*<<< orphan*/  ticket; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  kdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_list_put (scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_ctx_put (TYPE_4__*) ; 
 int /*<<< orphan*/  amdgpu_job_free (scalar_t__) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_syncobj_put (TYPE_2__) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_cs_parser_fini(struct amdgpu_cs_parser *parser, int error,
				  bool backoff)
{
	unsigned i;

	if (error && backoff)
		ttm_eu_backoff_reservation(&parser->ticket,
					   &parser->validated);

	for (i = 0; i < parser->num_post_dep_syncobjs; i++)
		drm_syncobj_put(parser->post_dep_syncobjs[i]);
	kfree(parser->post_dep_syncobjs);

	dma_fence_put(parser->fence);

	if (parser->ctx) {
		mutex_unlock(&parser->ctx->lock);
		amdgpu_ctx_put(parser->ctx);
	}
	if (parser->bo_list)
		amdgpu_bo_list_put(parser->bo_list);

	for (i = 0; i < parser->nchunks; i++)
		kvfree(parser->chunks[i].kdata);
	kfree(parser->chunks);
	if (parser->job)
		amdgpu_job_free(parser->job);
	amdgpu_bo_unref(&parser->uf_entry.robj);
}