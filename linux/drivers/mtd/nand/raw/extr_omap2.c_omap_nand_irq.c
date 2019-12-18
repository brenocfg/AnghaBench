#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  IO_ADDR_R; int /*<<< orphan*/  IO_ADDR_W; } ;
struct TYPE_6__ {TYPE_2__ legacy; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpmc_prefetch_status; } ;
struct omap_nand_info {scalar_t__ iomode; int gpmc_irq_count; int buf_len; int gpmc_irq_fifo; int /*<<< orphan*/  comp; scalar_t__ buf; TYPE_3__ nand; TYPE_1__ reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ OMAP_NAND_IO_WRITE ; 
 int PREFETCH_STATUS_FIFO_CNT (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  ioread32_rep (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  iowrite32_rep (int /*<<< orphan*/ ,int*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t omap_nand_irq(int this_irq, void *dev)
{
	struct omap_nand_info *info = (struct omap_nand_info *) dev;
	u32 bytes;

	bytes = readl(info->reg.gpmc_prefetch_status);
	bytes = PREFETCH_STATUS_FIFO_CNT(bytes);
	bytes = bytes  & 0xFFFC; /* io in multiple of 4 bytes */
	if (info->iomode == OMAP_NAND_IO_WRITE) { /* checks for write io */
		if (this_irq == info->gpmc_irq_count)
			goto done;

		if (info->buf_len && (info->buf_len < bytes))
			bytes = info->buf_len;
		else if (!info->buf_len)
			bytes = 0;
		iowrite32_rep(info->nand.legacy.IO_ADDR_W, (u32 *)info->buf,
			      bytes >> 2);
		info->buf = info->buf + bytes;
		info->buf_len -= bytes;

	} else {
		ioread32_rep(info->nand.legacy.IO_ADDR_R, (u32 *)info->buf,
			     bytes >> 2);
		info->buf = info->buf + bytes;

		if (this_irq == info->gpmc_irq_count)
			goto done;
	}

	return IRQ_HANDLED;

done:
	complete(&info->comp);

	disable_irq_nosync(info->gpmc_irq_fifo);
	disable_irq_nosync(info->gpmc_irq_count);

	return IRQ_HANDLED;
}