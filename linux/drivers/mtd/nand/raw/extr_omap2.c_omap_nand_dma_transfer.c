#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_10__ {int options; } ;
struct TYPE_8__ {int /*<<< orphan*/  gpmc_prefetch_status; } ;
struct omap_nand_info {TYPE_4__ nand; TYPE_5__* dma; int /*<<< orphan*/  gpmc_cs; TYPE_2__ reg; int /*<<< orphan*/  comp; TYPE_1__* pdev; } ;
struct mtd_info {int dummy; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/ * callback_param; int /*<<< orphan*/  callback; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_11__ {TYPE_3__* device; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int DMA_PREP_INTERRUPT ; 
 int DMA_TO_DEVICE ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  OMAP_NAND_TIMEOUT_MS ; 
 int /*<<< orphan*/  PREFETCH_FIFOTHRESHOLD_MAX ; 
 scalar_t__ PREFETCH_STATUS_COUNT (scalar_t__) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dma_async_issue_pending (TYPE_5__*) ; 
 unsigned int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (TYPE_5__*,struct scatterlist*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmaengine_submit (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 unsigned long loops_per_jiffy ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct omap_nand_info* mtd_to_omap (struct mtd_info*) ; 
 int /*<<< orphan*/  omap_nand_dma_callback ; 
 int omap_prefetch_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int,struct omap_nand_info*) ; 
 int /*<<< orphan*/  omap_prefetch_reset (int /*<<< orphan*/ ,struct omap_nand_info*) ; 
 int /*<<< orphan*/  omap_read_buf16 (struct mtd_info*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  omap_read_buf8 (struct mtd_info*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  omap_write_buf16 (struct mtd_info*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  omap_write_buf8 (struct mtd_info*,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,unsigned int) ; 
 int /*<<< orphan*/  virt_addr_valid (void*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int omap_nand_dma_transfer(struct mtd_info *mtd, void *addr,
					unsigned int len, int is_write)
{
	struct omap_nand_info *info = mtd_to_omap(mtd);
	struct dma_async_tx_descriptor *tx;
	enum dma_data_direction dir = is_write ? DMA_TO_DEVICE :
							DMA_FROM_DEVICE;
	struct scatterlist sg;
	unsigned long tim, limit;
	unsigned n;
	int ret;
	u32 val;

	if (!virt_addr_valid(addr))
		goto out_copy;

	sg_init_one(&sg, addr, len);
	n = dma_map_sg(info->dma->device->dev, &sg, 1, dir);
	if (n == 0) {
		dev_err(&info->pdev->dev,
			"Couldn't DMA map a %d byte buffer\n", len);
		goto out_copy;
	}

	tx = dmaengine_prep_slave_sg(info->dma, &sg, n,
		is_write ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM,
		DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!tx)
		goto out_copy_unmap;

	tx->callback = omap_nand_dma_callback;
	tx->callback_param = &info->comp;
	dmaengine_submit(tx);

	init_completion(&info->comp);

	/* setup and start DMA using dma_addr */
	dma_async_issue_pending(info->dma);

	/*  configure and start prefetch transfer */
	ret = omap_prefetch_enable(info->gpmc_cs,
		PREFETCH_FIFOTHRESHOLD_MAX, 0x1, len, is_write, info);
	if (ret)
		/* PFPW engine is busy, use cpu copy method */
		goto out_copy_unmap;

	wait_for_completion(&info->comp);
	tim = 0;
	limit = (loops_per_jiffy * msecs_to_jiffies(OMAP_NAND_TIMEOUT_MS));

	do {
		cpu_relax();
		val = readl(info->reg.gpmc_prefetch_status);
		val = PREFETCH_STATUS_COUNT(val);
	} while (val && (tim++ < limit));

	/* disable and stop the PFPW engine */
	omap_prefetch_reset(info->gpmc_cs, info);

	dma_unmap_sg(info->dma->device->dev, &sg, 1, dir);
	return 0;

out_copy_unmap:
	dma_unmap_sg(info->dma->device->dev, &sg, 1, dir);
out_copy:
	if (info->nand.options & NAND_BUSWIDTH_16)
		is_write == 0 ? omap_read_buf16(mtd, (u_char *) addr, len)
			: omap_write_buf16(mtd, (u_char *) addr, len);
	else
		is_write == 0 ? omap_read_buf8(mtd, (u_char *) addr, len)
			: omap_write_buf8(mtd, (u_char *) addr, len);
	return 0;
}