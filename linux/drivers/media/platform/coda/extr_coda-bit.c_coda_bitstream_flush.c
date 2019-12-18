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
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  vaddr; } ;
struct coda_ctx {scalar_t__ inst_type; TYPE_1__ bitstream; int /*<<< orphan*/  bitstream_fifo; TYPE_2__* dev; int /*<<< orphan*/  use_bit; } ;
struct TYPE_4__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_COMMAND_DEC_BUF_FLUSH ; 
 scalar_t__ CODA_INST_DECODER ; 
 int coda_command_sync (struct coda_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_kfifo_sync_to_device_full (struct coda_ctx*) ; 
 int /*<<< orphan*/  kfifo_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

int coda_bitstream_flush(struct coda_ctx *ctx)
{
	int ret;

	if (ctx->inst_type != CODA_INST_DECODER || !ctx->use_bit)
		return 0;

	ret = coda_command_sync(ctx, CODA_COMMAND_DEC_BUF_FLUSH);
	if (ret < 0) {
		v4l2_err(&ctx->dev->v4l2_dev, "failed to flush bitstream\n");
		return ret;
	}

	kfifo_init(&ctx->bitstream_fifo, ctx->bitstream.vaddr,
		   ctx->bitstream.size);
	coda_kfifo_sync_to_device_full(ctx);

	return 0;
}