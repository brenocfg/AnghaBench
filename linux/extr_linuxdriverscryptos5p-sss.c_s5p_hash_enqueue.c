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
struct s5p_hash_reqctx {int op_update; } ;
struct s5p_hash_ctx {int /*<<< orphan*/  dd; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 struct s5p_hash_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 struct s5p_hash_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int s5p_hash_handle_queue (int /*<<< orphan*/ ,struct ahash_request*) ; 

__attribute__((used)) static int s5p_hash_enqueue(struct ahash_request *req, bool op)
{
	struct s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	struct s5p_hash_ctx *tctx = crypto_tfm_ctx(req->base.tfm);

	ctx->op_update = op;

	return s5p_hash_handle_queue(tctx->dd, req);
}