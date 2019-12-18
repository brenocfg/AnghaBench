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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct coda_ctx {int /*<<< orphan*/  bitstream_fifo; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ kfifo_in (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static int coda_bitstream_queue(struct coda_ctx *ctx, const u8 *buf, u32 size)
{
	u32 n = kfifo_in(&ctx->bitstream_fifo, buf, size);

	return (n < size) ? -ENOSPC : 0;
}