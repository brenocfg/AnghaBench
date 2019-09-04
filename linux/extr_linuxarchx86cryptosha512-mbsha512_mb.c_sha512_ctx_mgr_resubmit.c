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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * buffer; } ;
struct sha512_hash_ctx {int status; scalar_t__ partial_block_buffer_length; int incoming_buffer_length; void* incoming_buffer; TYPE_1__ job; int /*<<< orphan*/  total_length; int /*<<< orphan*/ * partial_block_buffer; } ;
struct sha512_ctx_mgr {int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int HASH_CTX_STS_COMPLETE ; 
 int HASH_CTX_STS_IDLE ; 
 int HASH_CTX_STS_LAST ; 
 int HASH_CTX_STS_PROCESSING ; 
 int SHA512_BLOCK_SIZE ; 
 int SHA512_LOG2_BLOCK_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ sha512_job_mgr_submit (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int sha512_pad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sha512_hash_ctx *sha512_ctx_mgr_resubmit
		(struct sha512_ctx_mgr *mgr, struct sha512_hash_ctx *ctx)
{
	while (ctx) {
		if (ctx->status & HASH_CTX_STS_COMPLETE) {
			/* Clear PROCESSING bit */
			ctx->status = HASH_CTX_STS_COMPLETE;
			return ctx;
		}

		/*
		 * If the extra blocks are empty, begin hashing what remains
		 * in the user's buffer.
		 */
		if (ctx->partial_block_buffer_length == 0 &&
		    ctx->incoming_buffer_length) {

			const void *buffer = ctx->incoming_buffer;
			uint32_t len = ctx->incoming_buffer_length;
			uint32_t copy_len;

			/*
			 * Only entire blocks can be hashed.
			 * Copy remainder to extra blocks buffer.
			 */
			copy_len = len & (SHA512_BLOCK_SIZE-1);

			if (copy_len) {
				len -= copy_len;
				memcpy(ctx->partial_block_buffer,
				       ((const char *) buffer + len),
				       copy_len);
				ctx->partial_block_buffer_length = copy_len;
			}

			ctx->incoming_buffer_length = 0;

			/* len should be a multiple of the block size now */
			assert((len % SHA512_BLOCK_SIZE) == 0);

			/* Set len to the number of blocks to be hashed */
			len >>= SHA512_LOG2_BLOCK_SIZE;

			if (len) {

				ctx->job.buffer = (uint8_t *) buffer;
				ctx->job.len = len;
				ctx = (struct sha512_hash_ctx *)
					sha512_job_mgr_submit(&mgr->mgr,
					&ctx->job);
				continue;
			}
		}

		/*
		 * If the extra blocks are not empty, then we are
		 * either on the last block(s) or we need more
		 * user input before continuing.
		 */
		if (ctx->status & HASH_CTX_STS_LAST) {

			uint8_t *buf = ctx->partial_block_buffer;
			uint32_t n_extra_blocks =
					sha512_pad(buf, ctx->total_length);

			ctx->status = (HASH_CTX_STS_PROCESSING |
				       HASH_CTX_STS_COMPLETE);
			ctx->job.buffer = buf;
			ctx->job.len = (uint32_t) n_extra_blocks;
			ctx = (struct sha512_hash_ctx *)
				sha512_job_mgr_submit(&mgr->mgr, &ctx->job);
			continue;
		}

		if (ctx)
			ctx->status = HASH_CTX_STS_IDLE;
		return ctx;
	}

	return NULL;
}