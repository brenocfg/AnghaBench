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
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_SHA256 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_DIGEST_PRECOMPUTED ; 
 int /*<<< orphan*/  SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA256_H0 ; 
 int /*<<< orphan*/  SHA256_H1 ; 
 int /*<<< orphan*/  SHA256_H2 ; 
 int /*<<< orphan*/  SHA256_H3 ; 
 int /*<<< orphan*/  SHA256_H4 ; 
 int /*<<< orphan*/  SHA256_H5 ; 
 int /*<<< orphan*/  SHA256_H6 ; 
 int /*<<< orphan*/  SHA256_H7 ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 struct safexcel_ahash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memset (struct safexcel_ahash_req*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int safexcel_sha256_init(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	memset(req, 0, sizeof(*req));

	req->state[0] = SHA256_H0;
	req->state[1] = SHA256_H1;
	req->state[2] = SHA256_H2;
	req->state[3] = SHA256_H3;
	req->state[4] = SHA256_H4;
	req->state[5] = SHA256_H5;
	req->state[6] = SHA256_H6;
	req->state[7] = SHA256_H7;

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA256;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA256_DIGEST_SIZE;

	return 0;
}