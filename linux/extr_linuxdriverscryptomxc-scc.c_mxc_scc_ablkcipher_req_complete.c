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
struct mxc_scc_ctx {int ctrl; struct mxc_scc* scc; } ;
struct mxc_scc {int hw_busy; int /*<<< orphan*/  block_size_bytes; scalar_t__ base; int /*<<< orphan*/  memory_size_bytes; int /*<<< orphan*/  bytes_remaining; int /*<<< orphan*/ * req; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int) ;} ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int SCC_SCM_CTRL_CBC_MODE ; 
 scalar_t__ SCC_SCM_INIT_VECTOR_0 ; 
 struct ablkcipher_request* ablkcipher_request_cast (struct crypto_async_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int) ; 

__attribute__((used)) static int mxc_scc_ablkcipher_req_complete(struct crypto_async_request *req,
					   struct mxc_scc_ctx *ctx,
					   int result)
{
	struct ablkcipher_request *ablkreq = ablkcipher_request_cast(req);
	struct mxc_scc *scc = ctx->scc;

	scc->req = NULL;
	scc->bytes_remaining = scc->memory_size_bytes;

	if (ctx->ctrl & SCC_SCM_CTRL_CBC_MODE)
		memcpy(ablkreq->info, scc->base + SCC_SCM_INIT_VECTOR_0,
		       scc->block_size_bytes);

	req->complete(req, result);
	scc->hw_busy = false;

	return 0;
}