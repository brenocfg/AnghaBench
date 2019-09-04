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
struct sha256_hash_ctx {int dummy; } ;
struct mcryptd_hash_request_ctx {int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  waiter; } ;
struct mcryptd_alg_cstate {int /*<<< orphan*/  mgr; int /*<<< orphan*/  work_lock; } ;
struct ahash_request {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct mcryptd_hash_request_ctx* cast_hash_to_mcryptd_ctx (struct sha256_hash_ctx*) ; 
 struct ahash_request* cast_mcryptd_ctx_to_req (struct mcryptd_hash_request_ctx*) ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 struct sha256_hash_ctx* sha256_ctx_mgr_get_comp_ctx (int /*<<< orphan*/ ) ; 
 int sha_finish_walk (struct mcryptd_hash_request_ctx**,struct mcryptd_alg_cstate*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sha_complete_job(struct mcryptd_hash_request_ctx *rctx,
			    struct mcryptd_alg_cstate *cstate,
			    int err)
{
	struct ahash_request *req = cast_mcryptd_ctx_to_req(rctx);
	struct sha256_hash_ctx *sha_ctx;
	struct mcryptd_hash_request_ctx *req_ctx;
	int ret;

	/* remove from work list */
	spin_lock(&cstate->work_lock);
	list_del(&rctx->waiter);
	spin_unlock(&cstate->work_lock);

	if (irqs_disabled())
		rctx->complete(&req->base, err);
	else {
		local_bh_disable();
		rctx->complete(&req->base, err);
		local_bh_enable();
	}

	/* check to see if there are other jobs that are done */
	sha_ctx = sha256_ctx_mgr_get_comp_ctx(cstate->mgr);
	while (sha_ctx) {
		req_ctx = cast_hash_to_mcryptd_ctx(sha_ctx);
		ret = sha_finish_walk(&req_ctx, cstate, false);
		if (req_ctx) {
			spin_lock(&cstate->work_lock);
			list_del(&req_ctx->waiter);
			spin_unlock(&cstate->work_lock);

			req = cast_mcryptd_ctx_to_req(req_ctx);
			if (irqs_disabled())
				req_ctx->complete(&req->base, ret);
			else {
				local_bh_disable();
				req_ctx->complete(&req->base, ret);
				local_bh_enable();
			}
		}
		sha_ctx = sha256_ctx_mgr_get_comp_ctx(cstate->mgr);
	}

	return 0;
}