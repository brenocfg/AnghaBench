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
typedef  int /*<<< orphan*/  u32 ;
struct mv_cesa_engine {struct crypto_async_request* req; } ;
struct mv_cesa_ctx {TYPE_1__* ops; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
struct TYPE_2__ {int (* process ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* step ) (struct crypto_async_request*) ;int /*<<< orphan*/  (* complete ) (struct crypto_async_request*) ;} ;

/* Variables and functions */
 int EINPROGRESS ; 
 struct mv_cesa_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cesa_engine_enqueue_complete_request (struct mv_cesa_engine*,struct crypto_async_request*) ; 
 int stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct crypto_async_request*) ; 
 int /*<<< orphan*/  stub3 (struct crypto_async_request*) ; 

__attribute__((used)) static int mv_cesa_std_process(struct mv_cesa_engine *engine, u32 status)
{
	struct crypto_async_request *req;
	struct mv_cesa_ctx *ctx;
	int res;

	req = engine->req;
	ctx = crypto_tfm_ctx(req->tfm);
	res = ctx->ops->process(req, status);

	if (res == 0) {
		ctx->ops->complete(req);
		mv_cesa_engine_enqueue_complete_request(engine, req);
	} else if (res == -EINPROGRESS) {
		ctx->ops->step(req);
	}

	return res;
}