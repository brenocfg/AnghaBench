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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * buffer; } ;
struct sha256_hash_ctx {int status; scalar_t__ partial_block_buffer_length; TYPE_1__ job; int /*<<< orphan*/ * partial_block_buffer; scalar_t__ incoming_buffer_length; void const* incoming_buffer; int /*<<< orphan*/  total_length; int /*<<< orphan*/  error; } ;
struct sha256_ctx_mgr {int /*<<< orphan*/  mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_CTX_ERROR_ALREADY_COMPLETED ; 
 int /*<<< orphan*/  HASH_CTX_ERROR_ALREADY_PROCESSING ; 
 int /*<<< orphan*/  HASH_CTX_ERROR_INVALID_FLAGS ; 
 int /*<<< orphan*/  HASH_CTX_ERROR_NONE ; 
 int HASH_CTX_STS_COMPLETE ; 
 int HASH_CTX_STS_LAST ; 
 int HASH_CTX_STS_PROCESSING ; 
 int HASH_LAST ; 
 int HASH_UPDATE ; 
 scalar_t__ SHA256_BLOCK_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,scalar_t__) ; 
 struct sha256_hash_ctx* sha256_ctx_mgr_resubmit (struct sha256_ctx_mgr*,struct sha256_hash_ctx*) ; 
 scalar_t__ sha256_job_mgr_submit (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static struct sha256_hash_ctx *sha256_ctx_mgr_submit(struct sha256_ctx_mgr *mgr,
					  struct sha256_hash_ctx *ctx,
					  const void *buffer,
					  uint32_t len,
					  int flags)
{
	if (flags & ~(HASH_UPDATE | HASH_LAST)) {
		/* User should not pass anything other than UPDATE or LAST */
		ctx->error = HASH_CTX_ERROR_INVALID_FLAGS;
		return ctx;
	}

	if (ctx->status & HASH_CTX_STS_PROCESSING) {
		/* Cannot submit to a currently processing job. */
		ctx->error = HASH_CTX_ERROR_ALREADY_PROCESSING;
		return ctx;
	}

	if (ctx->status & HASH_CTX_STS_COMPLETE) {
		/* Cannot update a finished job. */
		ctx->error = HASH_CTX_ERROR_ALREADY_COMPLETED;
		return ctx;
	}

	/* If we made it here, there was no error during this call to submit */
	ctx->error = HASH_CTX_ERROR_NONE;

	/* Store buffer ptr info from user */
	ctx->incoming_buffer = buffer;
	ctx->incoming_buffer_length = len;

	/*
	 * Store the user's request flags and mark this ctx as currently
	 * being processed.
	 */
	ctx->status = (flags & HASH_LAST) ?
			(HASH_CTX_STS_PROCESSING | HASH_CTX_STS_LAST) :
			HASH_CTX_STS_PROCESSING;

	/* Advance byte counter */
	ctx->total_length += len;

	/*
	 * If there is anything currently buffered in the extra blocks,
	 * append to it until it contains a whole block.
	 * Or if the user's buffer contains less than a whole block,
	 * append as much as possible to the extra block.
	 */
	if (ctx->partial_block_buffer_length || len < SHA256_BLOCK_SIZE) {
		/*
		 * Compute how many bytes to copy from user buffer into
		 * extra block
		 */
		uint32_t copy_len = SHA256_BLOCK_SIZE -
					ctx->partial_block_buffer_length;
		if (len < copy_len)
			copy_len = len;

		if (copy_len) {
			/* Copy and update relevant pointers and counters */
			memcpy(
		&ctx->partial_block_buffer[ctx->partial_block_buffer_length],
				buffer, copy_len);

			ctx->partial_block_buffer_length += copy_len;
			ctx->incoming_buffer = (const void *)
					((const char *)buffer + copy_len);
			ctx->incoming_buffer_length = len - copy_len;
		}

		/* The extra block should never contain more than 1 block */
		assert(ctx->partial_block_buffer_length <= SHA256_BLOCK_SIZE);

		/*
		 * If the extra block buffer contains exactly 1 block,
		 * it can be hashed.
		 */
		if (ctx->partial_block_buffer_length >= SHA256_BLOCK_SIZE) {
			ctx->partial_block_buffer_length = 0;

			ctx->job.buffer = ctx->partial_block_buffer;
			ctx->job.len = 1;
			ctx = (struct sha256_hash_ctx *)
				sha256_job_mgr_submit(&mgr->mgr, &ctx->job);
		}
	}

	return sha256_ctx_mgr_resubmit(mgr, ctx);
}