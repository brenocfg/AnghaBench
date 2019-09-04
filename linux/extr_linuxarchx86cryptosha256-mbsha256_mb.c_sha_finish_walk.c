#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sha256_hash_ctx {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct mcryptd_hash_request_ctx {int flag; TYPE_1__ walk; int /*<<< orphan*/  areq; } ;
struct mcryptd_alg_cstate {int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int HASH_DONE ; 
 int HASH_FINAL ; 
 int HASH_LAST ; 
 int HASH_UPDATE ; 
 scalar_t__ ahash_request_ctx (int /*<<< orphan*/ *) ; 
 struct mcryptd_hash_request_ctx* cast_hash_to_mcryptd_ctx (struct sha256_hash_ctx*) ; 
 int crypto_ahash_walk_done (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ahash_walk_last (TYPE_1__*) ; 
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 
 struct sha256_hash_ctx* sha256_ctx_mgr_flush (int /*<<< orphan*/ ) ; 
 struct sha256_hash_ctx* sha256_ctx_mgr_submit (int /*<<< orphan*/ ,struct sha256_hash_ctx*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sha256_mb_set_results (struct mcryptd_hash_request_ctx*) ; 

__attribute__((used)) static int sha_finish_walk(struct mcryptd_hash_request_ctx **ret_rctx,
			struct mcryptd_alg_cstate *cstate, bool flush)
{
	int	flag = HASH_UPDATE;
	int	nbytes, err = 0;
	struct mcryptd_hash_request_ctx *rctx = *ret_rctx;
	struct sha256_hash_ctx *sha_ctx;

	/* more work ? */
	while (!(rctx->flag & HASH_DONE)) {
		nbytes = crypto_ahash_walk_done(&rctx->walk, 0);
		if (nbytes < 0) {
			err = nbytes;
			goto out;
		}
		/* check if the walk is done */
		if (crypto_ahash_walk_last(&rctx->walk)) {
			rctx->flag |= HASH_DONE;
			if (rctx->flag & HASH_FINAL)
				flag |= HASH_LAST;

		}
		sha_ctx = (struct sha256_hash_ctx *)
						ahash_request_ctx(&rctx->areq);
		kernel_fpu_begin();
		sha_ctx = sha256_ctx_mgr_submit(cstate->mgr, sha_ctx,
						rctx->walk.data, nbytes, flag);
		if (!sha_ctx) {
			if (flush)
				sha_ctx = sha256_ctx_mgr_flush(cstate->mgr);
		}
		kernel_fpu_end();
		if (sha_ctx)
			rctx = cast_hash_to_mcryptd_ctx(sha_ctx);
		else {
			rctx = NULL;
			goto out;
		}
	}

	/* copy the results */
	if (rctx->flag & HASH_FINAL)
		sha256_mb_set_results(rctx);

out:
	*ret_rctx = rctx;
	return err;
}