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
struct TYPE_2__ {int /*<<< orphan*/ * result_digest; } ;
struct sha256_hash_ctx {int /*<<< orphan*/  status; scalar_t__ partial_block_buffer_length; scalar_t__ total_length; TYPE_1__ job; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_CTX_STS_IDLE ; 
 int /*<<< orphan*/  SHA256_H0 ; 
 int /*<<< orphan*/  SHA256_H1 ; 
 int /*<<< orphan*/  SHA256_H2 ; 
 int /*<<< orphan*/  SHA256_H3 ; 
 int /*<<< orphan*/  SHA256_H4 ; 
 int /*<<< orphan*/  SHA256_H5 ; 
 int /*<<< orphan*/  SHA256_H6 ; 
 int /*<<< orphan*/  SHA256_H7 ; 
 struct sha256_hash_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  hash_ctx_init (struct sha256_hash_ctx*) ; 

__attribute__((used)) static int sha256_mb_init(struct ahash_request *areq)
{
	struct sha256_hash_ctx *sctx = ahash_request_ctx(areq);

	hash_ctx_init(sctx);
	sctx->job.result_digest[0] = SHA256_H0;
	sctx->job.result_digest[1] = SHA256_H1;
	sctx->job.result_digest[2] = SHA256_H2;
	sctx->job.result_digest[3] = SHA256_H3;
	sctx->job.result_digest[4] = SHA256_H4;
	sctx->job.result_digest[5] = SHA256_H5;
	sctx->job.result_digest[6] = SHA256_H6;
	sctx->job.result_digest[7] = SHA256_H7;
	sctx->total_length = 0;
	sctx->partial_block_buffer_length = 0;
	sctx->status = HASH_CTX_STS_IDLE;

	return 0;
}