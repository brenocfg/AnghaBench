#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  size; } ;
struct coda_ctx {int /*<<< orphan*/  bitstream_fifo; TYPE_2__ bitstream; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void coda_free_bitstream_buffer(struct coda_ctx *ctx)
{
	if (ctx->bitstream.vaddr == NULL)
		return;

	dma_free_wc(ctx->dev->dev, ctx->bitstream.size, ctx->bitstream.vaddr,
		    ctx->bitstream.paddr);
	ctx->bitstream.vaddr = NULL;
	kfifo_init(&ctx->bitstream_fifo, NULL, 0);
}