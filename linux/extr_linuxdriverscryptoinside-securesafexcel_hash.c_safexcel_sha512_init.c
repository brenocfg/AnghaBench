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
struct safexcel_ahash_req {int /*<<< orphan*/  state_sz; int /*<<< orphan*/  digest; void** state; } ;
struct safexcel_ahash_ctx {int /*<<< orphan*/  alg; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL_CRYPTO_ALG_SHA512 ; 
 int /*<<< orphan*/  CONTEXT_CONTROL_DIGEST_PRECOMPUTED ; 
 int /*<<< orphan*/  SHA512_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA512_H0 ; 
 int /*<<< orphan*/  SHA512_H1 ; 
 int /*<<< orphan*/  SHA512_H2 ; 
 int /*<<< orphan*/  SHA512_H3 ; 
 int /*<<< orphan*/  SHA512_H4 ; 
 int /*<<< orphan*/  SHA512_H5 ; 
 int /*<<< orphan*/  SHA512_H6 ; 
 int /*<<< orphan*/  SHA512_H7 ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 struct safexcel_ahash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct safexcel_ahash_req*,int /*<<< orphan*/ ,int) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int safexcel_sha512_init(struct ahash_request *areq)
{
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);

	memset(req, 0, sizeof(*req));

	req->state[0] = lower_32_bits(SHA512_H0);
	req->state[1] = upper_32_bits(SHA512_H0);
	req->state[2] = lower_32_bits(SHA512_H1);
	req->state[3] = upper_32_bits(SHA512_H1);
	req->state[4] = lower_32_bits(SHA512_H2);
	req->state[5] = upper_32_bits(SHA512_H2);
	req->state[6] = lower_32_bits(SHA512_H3);
	req->state[7] = upper_32_bits(SHA512_H3);
	req->state[8] = lower_32_bits(SHA512_H4);
	req->state[9] = upper_32_bits(SHA512_H4);
	req->state[10] = lower_32_bits(SHA512_H5);
	req->state[11] = upper_32_bits(SHA512_H5);
	req->state[12] = lower_32_bits(SHA512_H6);
	req->state[13] = upper_32_bits(SHA512_H6);
	req->state[14] = lower_32_bits(SHA512_H7);
	req->state[15] = upper_32_bits(SHA512_H7);

	ctx->alg = CONTEXT_CONTROL_CRYPTO_ALG_SHA512;
	req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
	req->state_sz = SHA512_DIGEST_SIZE;

	return 0;
}