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
struct crypto_async_request {int dummy; } ;
struct cryptd_hash_request_ctx {int /*<<< orphan*/  complete; int /*<<< orphan*/  desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  complete; } ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct cryptd_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  cryptd_hash_complete (struct ahash_request*,int) ; 
 int shash_ahash_update (struct ahash_request*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cryptd_hash_update(struct crypto_async_request *req_async, int err)
{
	struct ahash_request *req = ahash_request_cast(req_async);
	struct cryptd_hash_request_ctx *rctx;

	rctx = ahash_request_ctx(req);

	if (unlikely(err == -EINPROGRESS))
		goto out;

	err = shash_ahash_update(req, &rctx->desc);

	req->base.complete = rctx->complete;

out:
	cryptd_hash_complete(req, err);
}