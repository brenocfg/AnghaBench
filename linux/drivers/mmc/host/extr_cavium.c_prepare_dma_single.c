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
typedef  int u64 ;
struct mmc_data {int flags; int /*<<< orphan*/ * sg; int /*<<< orphan*/  sg_len; } ;
struct cvm_mmc_host {scalar_t__ dma_base; scalar_t__ big_dma_addr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ MIO_EMM_DMA_ADR (struct cvm_mmc_host*) ; 
 scalar_t__ MIO_EMM_DMA_CFG (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  MIO_EMM_DMA_CFG_ADR ; 
 int /*<<< orphan*/  MIO_EMM_DMA_CFG_EN ; 
 int /*<<< orphan*/  MIO_EMM_DMA_CFG_ENDIAN ; 
 int /*<<< orphan*/  MIO_EMM_DMA_CFG_RW ; 
 int /*<<< orphan*/  MIO_EMM_DMA_CFG_SIZE ; 
 int MMC_DATA_WRITE ; 
 int dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_dir (struct mmc_data*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int) ; 
 int sg_dma_address (int /*<<< orphan*/ *) ; 
 int sg_dma_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static u64 prepare_dma_single(struct cvm_mmc_host *host, struct mmc_data *data)
{
	u64 dma_cfg, addr;
	int count, rw;

	count = dma_map_sg(host->dev, data->sg, data->sg_len,
			   get_dma_dir(data));
	if (!count)
		return 0;

	rw = (data->flags & MMC_DATA_WRITE) ? 1 : 0;
	dma_cfg = FIELD_PREP(MIO_EMM_DMA_CFG_EN, 1) |
		  FIELD_PREP(MIO_EMM_DMA_CFG_RW, rw);
#ifdef __LITTLE_ENDIAN
	dma_cfg |= FIELD_PREP(MIO_EMM_DMA_CFG_ENDIAN, 1);
#endif
	dma_cfg |= FIELD_PREP(MIO_EMM_DMA_CFG_SIZE,
			      (sg_dma_len(&data->sg[0]) / 8) - 1);

	addr = sg_dma_address(&data->sg[0]);
	if (!host->big_dma_addr)
		dma_cfg |= FIELD_PREP(MIO_EMM_DMA_CFG_ADR, addr);
	writeq(dma_cfg, host->dma_base + MIO_EMM_DMA_CFG(host));

	pr_debug("[%s] sg_dma_len: %u  total sg_elem: %d\n",
		 (rw) ? "W" : "R", sg_dma_len(&data->sg[0]), count);

	if (host->big_dma_addr)
		writeq(addr, host->dma_base + MIO_EMM_DMA_ADR(host));
	return addr;
}