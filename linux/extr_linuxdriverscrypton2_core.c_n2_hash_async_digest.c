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
struct n2_hash_req_ctx {int /*<<< orphan*/  u; } ;
struct n2_ahash_alg {int digest_size; int hw_op_hashsz; int /*<<< orphan*/  auth_type; int /*<<< orphan*/  hash_init; int /*<<< orphan*/  hash_zero; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {scalar_t__ nbytes; int /*<<< orphan*/ * result; TYPE_1__ base; } ;

/* Variables and functions */
 struct n2_hash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct n2_ahash_alg* n2_ahash_alg (int /*<<< orphan*/ ) ; 
 int n2_do_async_digest (struct ahash_request*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int n2_hash_async_digest(struct ahash_request *req)
{
	struct n2_ahash_alg *n2alg = n2_ahash_alg(req->base.tfm);
	struct n2_hash_req_ctx *rctx = ahash_request_ctx(req);
	int ds;

	ds = n2alg->digest_size;
	if (unlikely(req->nbytes == 0)) {
		memcpy(req->result, n2alg->hash_zero, ds);
		return 0;
	}
	memcpy(&rctx->u, n2alg->hash_init, n2alg->hw_op_hashsz);

	return n2_do_async_digest(req, n2alg->auth_type,
				  n2alg->hw_op_hashsz, ds,
				  &rctx->u, 0UL, 0);
}