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
struct coda_q_data {int sizeimage; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; scalar_t__ vaddr; int /*<<< orphan*/  paddr; } ;
struct coda_ctx {TYPE_2__ bitstream; int /*<<< orphan*/  bitstream_fifo; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ dma_alloc_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_init (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int coda_alloc_bitstream_buffer(struct coda_ctx *ctx,
				       struct coda_q_data *q_data)
{
	if (ctx->bitstream.vaddr)
		return 0;

	ctx->bitstream.size = roundup_pow_of_two(q_data->sizeimage * 2);
	ctx->bitstream.vaddr = dma_alloc_wc(ctx->dev->dev, ctx->bitstream.size,
					    &ctx->bitstream.paddr, GFP_KERNEL);
	if (!ctx->bitstream.vaddr) {
		v4l2_err(&ctx->dev->v4l2_dev,
			 "failed to allocate bitstream ringbuffer");
		return -ENOMEM;
	}
	kfifo_init(&ctx->bitstream_fifo,
		   ctx->bitstream.vaddr, ctx->bitstream.size);

	return 0;
}