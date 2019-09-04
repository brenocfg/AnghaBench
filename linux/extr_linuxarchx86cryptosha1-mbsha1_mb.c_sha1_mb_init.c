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
struct sha1_hash_ctx {int /*<<< orphan*/  status; scalar_t__ partial_block_buffer_length; scalar_t__ total_length; TYPE_1__ job; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_CTX_STS_IDLE ; 
 int /*<<< orphan*/  SHA1_H0 ; 
 int /*<<< orphan*/  SHA1_H1 ; 
 int /*<<< orphan*/  SHA1_H2 ; 
 int /*<<< orphan*/  SHA1_H3 ; 
 int /*<<< orphan*/  SHA1_H4 ; 
 struct sha1_hash_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  hash_ctx_init (struct sha1_hash_ctx*) ; 

__attribute__((used)) static int sha1_mb_init(struct ahash_request *areq)
{
	struct sha1_hash_ctx *sctx = ahash_request_ctx(areq);

	hash_ctx_init(sctx);
	sctx->job.result_digest[0] = SHA1_H0;
	sctx->job.result_digest[1] = SHA1_H1;
	sctx->job.result_digest[2] = SHA1_H2;
	sctx->job.result_digest[3] = SHA1_H3;
	sctx->job.result_digest[4] = SHA1_H4;
	sctx->total_length = 0;
	sctx->partial_block_buffer_length = 0;
	sctx->status = HASH_CTX_STS_IDLE;

	return 0;
}