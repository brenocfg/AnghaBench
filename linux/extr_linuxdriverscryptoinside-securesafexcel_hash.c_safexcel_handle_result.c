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
struct safexcel_crypto_priv {int flags; } ;
struct safexcel_ahash_req {int needs_inv; } ;
struct crypto_async_request {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIP197_TRC_CACHE ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int safexcel_handle_inv_result (struct safexcel_crypto_priv*,int,struct crypto_async_request*,int*,int*) ; 
 int safexcel_handle_req_result (struct safexcel_crypto_priv*,int,struct crypto_async_request*,int*,int*) ; 

__attribute__((used)) static int safexcel_handle_result(struct safexcel_crypto_priv *priv, int ring,
				  struct crypto_async_request *async,
				  bool *should_complete, int *ret)
{
	struct ahash_request *areq = ahash_request_cast(async);
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	int err;

	BUG_ON(!(priv->flags & EIP197_TRC_CACHE) && req->needs_inv);

	if (req->needs_inv) {
		req->needs_inv = false;
		err = safexcel_handle_inv_result(priv, ring, async,
						 should_complete, ret);
	} else {
		err = safexcel_handle_req_result(priv, ring, async,
						 should_complete, ret);
	}

	return err;
}