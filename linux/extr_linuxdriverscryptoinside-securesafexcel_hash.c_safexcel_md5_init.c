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
struct safexcel_ahash_req {int /*<<< orphan*/  state_sz; int /*<<< orphan*/  digest; int /*<<< orphan*/ * state; } ;
struct safexcel_ahash_ctx {int /*<<< orphan*/  alg; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_MD5 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_DIGEST_PRECOMPUTED ; 
 int /*<<< orphan*/  MD5_DIGEST_SIZE ; 
 int /*<<< orphan*/  MD5_H0 ; 
 int /*<<< orphan*/  MD5_H1 ; 
 int /*<<< orphan*/  MD5_H2 ; 
 int /*<<< orphan*/  MD5_H3 ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 struct safexcel_ahash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memset (struct safexcel_ahash_req*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int safexcel_md5_init(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	memset(req, 0, sizeof(*req));

	req->state[0] = MD5_H0;
	req->state[1] = MD5_H1;
	req->state[2] = MD5_H2;
	req->state[3] = MD5_H3;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_MD5;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = MD5_DIGEST_SIZE;

	return 0;
}