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
struct safexcel_ahash_req {int last_req; int finish; int /*<<< orphan*/ * len; } ;
struct safexcel_ahash_ctx {scalar_t__ alg; } ;
struct ahash_request {int /*<<< orphan*/  result; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_MD5 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA1 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA224 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA256 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA384 ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_ALG_SHA512 ; 
 int /*<<< orphan*/  MD5_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA1_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA224_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA384_DIGEST_SIZE ; 
 int /*<<< orphan*/  SHA512_DIGEST_SIZE ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 struct safexcel_ahash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  md5_zero_message_hash ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int safexcel_ahash_enqueue (struct ahash_request*) ; 
 int /*<<< orphan*/  sha1_zero_message_hash ; 
 int /*<<< orphan*/  sha224_zero_message_hash ; 
 int /*<<< orphan*/  sha256_zero_message_hash ; 
 int /*<<< orphan*/  sha384_zero_message_hash ; 
 int /*<<< orphan*/  sha512_zero_message_hash ; 

__attribute__((used)) static int safexcel_ahash_final(struct ahash_request *areq)
{
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	struct safexcel_ahash_ctx *ctx = crypto_ahash_ctx(crypto_ahash_reqtfm(areq));

	req->last_req = true;
	req->finish = true;

	/* If we have an overall 0 length request */
	if (!req->len[0] && !req->len[1] && !areq->nbytes) {
		if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_MD5)
			memcpy(areq->result, md5_zero_message_hash,
			       MD5_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA1)
			memcpy(areq->result, sha1_zero_message_hash,
			       SHA1_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA224)
			memcpy(areq->result, sha224_zero_message_hash,
			       SHA224_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA256)
			memcpy(areq->result, sha256_zero_message_hash,
			       SHA256_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA384)
			memcpy(areq->result, sha384_zero_message_hash,
			       SHA384_DIGEST_SIZE);
		else if (ctx->alg == CONTEXT_CONTROL_CRYPTO_ALG_SHA512)
			memcpy(areq->result, sha512_zero_message_hash,
			       SHA512_DIGEST_SIZE);

		return 0;
	}

	return safexcel_ahash_enqueue(areq);
}