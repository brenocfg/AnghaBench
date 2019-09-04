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
struct TYPE_2__ {int /*<<< orphan*/  ctxr_dma; } ;
struct safexcel_ahash_ctx {TYPE_1__ base; int /*<<< orphan*/  priv; } ;
struct crypto_async_request {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct safexcel_ahash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int safexcel_invalidate_cache (struct crypto_async_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int safexcel_ahash_send_inv(struct crypto_async_request *async,
				   int ring, int *commands, int *results)
{
	struct ahash_request *areq = ahash_request_cast(async);
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	int ret;

	ret = safexcel_invalidate_cache(async, ctx->priv,
					ctx->base.ctxr_dma, ring);
	if (unlikely(ret))
		return ret;

	*commands = 1;
	*results = 1;

	return 0;
}