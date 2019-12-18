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
typedef  scalar_t__ u32 ;
struct coda_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ paddr; } ;
struct __kfifo {int out; int mask; int in; } ;
struct TYPE_4__ {struct __kfifo kfifo; } ;
struct coda_ctx {int /*<<< orphan*/  reg_idx; TYPE_1__ bitstream; struct coda_dev* dev; TYPE_2__ bitstream_fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA_REG_BIT_RD_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODA_REG_BIT_WR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_write (struct coda_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void coda_kfifo_sync_to_device_full(struct coda_ctx *ctx)
{
	struct __kfifo *kfifo = &ctx->bitstream_fifo.kfifo;
	struct coda_dev *dev = ctx->dev;
	u32 rd_ptr, wr_ptr;

	rd_ptr = ctx->bitstream.paddr + (kfifo->out & kfifo->mask);
	coda_write(dev, rd_ptr, CODA_REG_BIT_RD_PTR(ctx->reg_idx));
	wr_ptr = ctx->bitstream.paddr + (kfifo->in & kfifo->mask);
	coda_write(dev, wr_ptr, CODA_REG_BIT_WR_PTR(ctx->reg_idx));
}