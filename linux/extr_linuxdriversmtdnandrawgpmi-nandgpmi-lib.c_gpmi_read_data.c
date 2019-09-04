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
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct gpmi_nand_data {int current_chip; int /*<<< orphan*/  data_buffer_dma; struct scatterlist data_sgl; int /*<<< orphan*/  dev; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BF_GPMI_CTRL0_ADDRESS (int /*<<< orphan*/ ) ; 
 int BF_GPMI_CTRL0_COMMAND_MODE (int /*<<< orphan*/ ) ; 
 int BF_GPMI_CTRL0_CS (int,struct gpmi_nand_data*) ; 
 int BF_GPMI_CTRL0_LOCK_CS (int /*<<< orphan*/ ,struct gpmi_nand_data*) ; 
 int BF_GPMI_CTRL0_XFER_COUNT (int) ; 
 int BM_GPMI_CTRL0_WORD_LENGTH ; 
 int /*<<< orphan*/  BV_GPMI_CTRL0_ADDRESS__NAND_DATA ; 
 int /*<<< orphan*/  BV_GPMI_CTRL0_COMMAND_MODE__READ ; 
 int DMA_CTRL_ACK ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TRANS_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_CS_ENABLE ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,struct scatterlist*,int,int /*<<< orphan*/ ,int) ; 
 struct dma_chan* get_dma_chan (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int prepare_data_dma (struct gpmi_nand_data*,void*,int,int /*<<< orphan*/ ) ; 
 int start_dma_without_bch_irq (struct gpmi_nand_data*,struct dma_async_tx_descriptor*) ; 

int gpmi_read_data(struct gpmi_nand_data *this, void *buf, int len)
{
	struct dma_async_tx_descriptor *desc;
	struct dma_chan *channel = get_dma_chan(this);
	int chip = this->current_chip;
	int ret;
	u32 pio[2];
	bool direct;

	/* [1] : send PIO */
	pio[0] = BF_GPMI_CTRL0_COMMAND_MODE(BV_GPMI_CTRL0_COMMAND_MODE__READ)
		| BM_GPMI_CTRL0_WORD_LENGTH
		| BF_GPMI_CTRL0_CS(chip, this)
		| BF_GPMI_CTRL0_LOCK_CS(LOCK_CS_ENABLE, this)
		| BF_GPMI_CTRL0_ADDRESS(BV_GPMI_CTRL0_ADDRESS__NAND_DATA)
		| BF_GPMI_CTRL0_XFER_COUNT(len);
	pio[1] = 0;
	desc = dmaengine_prep_slave_sg(channel,
					(struct scatterlist *)pio,
					ARRAY_SIZE(pio), DMA_TRANS_NONE, 0);
	if (!desc)
		return -EINVAL;

	/* [2] : send DMA request */
	direct = prepare_data_dma(this, buf, len, DMA_FROM_DEVICE);
	desc = dmaengine_prep_slave_sg(channel, &this->data_sgl,
					1, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc)
		return -EINVAL;

	/* [3] : submit the DMA */

	ret = start_dma_without_bch_irq(this, desc);

	dma_unmap_sg(this->dev, &this->data_sgl, 1, DMA_FROM_DEVICE);
	if (!direct)
		memcpy(buf, this->data_buffer_dma, len);

	return ret;
}