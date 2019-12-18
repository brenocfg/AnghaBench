#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ddb_regmap {TYPE_4__* idma_buf; TYPE_3__* idma; TYPE_2__* odma_buf; TYPE_1__* odma; } ;
struct ddb_io {int /*<<< orphan*/  nr; TYPE_5__* port; struct ddb_dma* dma; } ;
struct ddb_dma {int size; int div; scalar_t__ bufregs; scalar_t__ regs; void* num; int /*<<< orphan*/  work; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; struct ddb_io* io; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; struct ddb_dma* idma; struct ddb_dma* odma; } ;
struct TYPE_11__ {int /*<<< orphan*/  lnr; TYPE_6__* dev; } ;
struct TYPE_10__ {int size; scalar_t__ base; } ;
struct TYPE_9__ {int size; scalar_t__ base; } ;
struct TYPE_8__ {int size; scalar_t__ base; } ;
struct TYPE_7__ {int size; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFFER_ACK (struct ddb_dma*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddbwritel (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 void* dma_buf_num ; 
 int dma_buf_size ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_work ; 
 struct ddb_regmap* io_regmap (struct ddb_io*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ddb_dma_init(struct ddb_io *io, int nr, int out)
{
	struct ddb_dma *dma;
	const struct ddb_regmap *rm = io_regmap(io, 0);

	dma = out ? &io->port->dev->odma[nr] : &io->port->dev->idma[nr];
	io->dma = dma;
	dma->io = io;

	spin_lock_init(&dma->lock);
	init_waitqueue_head(&dma->wq);
	if (out) {
		INIT_WORK(&dma->work, output_work);
		dma->regs = rm->odma->base + rm->odma->size * nr;
		dma->bufregs = rm->odma_buf->base + rm->odma_buf->size * nr;
		dma->num = dma_buf_num;
		dma->size = dma_buf_size * 128 * 47;
		dma->div = 1;
	} else {
		INIT_WORK(&dma->work, input_work);
		dma->regs = rm->idma->base + rm->idma->size * nr;
		dma->bufregs = rm->idma_buf->base + rm->idma_buf->size * nr;
		dma->num = dma_buf_num;
		dma->size = dma_buf_size * 128 * 47;
		dma->div = 1;
	}
	ddbwritel(io->port->dev, 0, DMA_BUFFER_ACK(dma));
	dev_dbg(io->port->dev->dev, "init link %u, io %u, dma %u, dmaregs %08x bufregs %08x\n",
		io->port->lnr, io->nr, nr, dma->regs, dma->bufregs);
}