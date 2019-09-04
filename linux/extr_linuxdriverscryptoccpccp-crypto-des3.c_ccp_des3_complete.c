#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct crypto_async_request {int dummy; } ;
struct ccp_des3_req_ctx {int /*<<< orphan*/  iv; } ;
struct TYPE_5__ {scalar_t__ mode; } ;
struct TYPE_6__ {TYPE_2__ des3; } ;
struct ccp_ctx {TYPE_3__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  tfm; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ CCP_DES3_MODE_ECB ; 
 int /*<<< orphan*/  DES3_EDE_BLOCK_SIZE ; 
 struct ablkcipher_request* ablkcipher_request_cast (struct crypto_async_request*) ; 
 struct ccp_des3_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 struct ccp_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccp_des3_complete(struct crypto_async_request *async_req, int ret)
{
	struct ablkcipher_request *req = ablkcipher_request_cast(async_req);
	struct ccp_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	struct ccp_des3_req_ctx *rctx = ablkcipher_request_ctx(req);

	if (ret)
		return ret;

	if (ctx->u.des3.mode != CCP_DES3_MODE_ECB)
		memcpy(req->info, rctx->iv, DES3_EDE_BLOCK_SIZE);

	return 0;
}