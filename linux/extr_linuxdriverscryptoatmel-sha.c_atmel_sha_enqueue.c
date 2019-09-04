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
struct atmel_sha_reqctx {unsigned int op; } ;
struct atmel_sha_dev {int dummy; } ;
struct atmel_sha_ctx {struct atmel_sha_dev* dd; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int atmel_sha_handle_queue (struct atmel_sha_dev*,struct ahash_request*) ; 
 struct atmel_sha_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_sha_enqueue(struct ahash_request *req, unsigned int op)
{
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	struct atmel_sha_ctx *tctx = crypto_tfm_ctx(req->base.tfm);
	struct atmel_sha_dev *dd = tctx->dd;

	ctx->op = op;

	return atmel_sha_handle_queue(dd, req);
}