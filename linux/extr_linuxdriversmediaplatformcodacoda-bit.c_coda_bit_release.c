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
struct coda_ctx {int /*<<< orphan*/  buffer_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  coda_free_bitstream_buffer (struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_free_context_buffers (struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_free_framebuffers (struct coda_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void coda_bit_release(struct coda_ctx *ctx)
{
	mutex_lock(&ctx->buffer_mutex);
	coda_free_framebuffers(ctx);
	coda_free_context_buffers(ctx);
	coda_free_bitstream_buffer(ctx);
	mutex_unlock(&ctx->buffer_mutex);
}