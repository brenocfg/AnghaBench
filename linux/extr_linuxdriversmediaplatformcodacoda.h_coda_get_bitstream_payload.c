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
struct coda_ctx {int /*<<< orphan*/  bitstream_fifo; } ;

/* Variables and functions */
 unsigned int kfifo_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int coda_get_bitstream_payload(struct coda_ctx *ctx)
{
	return kfifo_len(&ctx->bitstream_fifo);
}