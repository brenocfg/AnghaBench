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
typedef  int uint32_t ;
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct bch_geometry {int page_size; } ;
struct gpmi_nand_data {int current_chip; struct bch_geometry bch_geometry; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BF_GPMI_CTRL0_ADDRESS (int) ; 
 int BF_GPMI_CTRL0_COMMAND_MODE (int) ; 
 int BF_GPMI_CTRL0_CS (int,struct gpmi_nand_data*) ; 
 int BF_GPMI_CTRL0_LOCK_CS (int /*<<< orphan*/ ,struct gpmi_nand_data*) ; 
 int BF_GPMI_CTRL0_XFER_COUNT (int) ; 
 int BF_GPMI_ECCCTRL_BUFFER_MASK (int) ; 
 int BF_GPMI_ECCCTRL_ECC_CMD (int) ; 
 int BM_GPMI_CTRL0_WORD_LENGTH ; 
 int BM_GPMI_ECCCTRL_ENABLE_ECC ; 
 int BV_GPMI_CTRL0_ADDRESS__NAND_DATA ; 
 int BV_GPMI_CTRL0_COMMAND_MODE__READ ; 
 int BV_GPMI_CTRL0_COMMAND_MODE__WAIT_FOR_READY ; 
 int BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_AUXONLY ; 
 int BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_PAGE ; 
 int BV_GPMI_ECCCTRL_ECC_CMD__BCH_DECODE ; 
 int DMA_CTRL_ACK ; 
 int DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  DMA_TRANS_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_CS_ENABLE ; 
 struct dma_async_tx_descriptor* dmaengine_prep_slave_sg (struct dma_chan*,struct scatterlist*,int,int /*<<< orphan*/ ,int) ; 
 struct dma_chan* get_dma_chan (struct gpmi_nand_data*) ; 
 int start_dma_with_bch_irq (struct gpmi_nand_data*,struct dma_async_tx_descriptor*) ; 

int gpmi_read_page(struct gpmi_nand_data *this,
				dma_addr_t payload, dma_addr_t auxiliary)
{
	struct bch_geometry *geo = &this->bch_geometry;
	uint32_t command_mode;
	uint32_t address;
	uint32_t ecc_command;
	uint32_t buffer_mask;
	struct dma_async_tx_descriptor *desc;
	struct dma_chan *channel = get_dma_chan(this);
	int chip = this->current_chip;
	u32 pio[6];

	/* [1] Wait for the chip to report ready. */
	command_mode = BV_GPMI_CTRL0_COMMAND_MODE__WAIT_FOR_READY;
	address      = BV_GPMI_CTRL0_ADDRESS__NAND_DATA;

	pio[0] =  BF_GPMI_CTRL0_COMMAND_MODE(command_mode)
		| BM_GPMI_CTRL0_WORD_LENGTH
		| BF_GPMI_CTRL0_CS(chip, this)
		| BF_GPMI_CTRL0_LOCK_CS(LOCK_CS_ENABLE, this)
		| BF_GPMI_CTRL0_ADDRESS(address)
		| BF_GPMI_CTRL0_XFER_COUNT(0);
	pio[1] = 0;
	desc = dmaengine_prep_slave_sg(channel,
				(struct scatterlist *)pio, 2,
				DMA_TRANS_NONE, 0);
	if (!desc)
		return -EINVAL;

	/* [2] Enable the BCH block and read. */
	command_mode = BV_GPMI_CTRL0_COMMAND_MODE__READ;
	address      = BV_GPMI_CTRL0_ADDRESS__NAND_DATA;
	ecc_command  = BV_GPMI_ECCCTRL_ECC_CMD__BCH_DECODE;
	buffer_mask  = BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_PAGE
			| BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_AUXONLY;

	pio[0] =  BF_GPMI_CTRL0_COMMAND_MODE(command_mode)
		| BM_GPMI_CTRL0_WORD_LENGTH
		| BF_GPMI_CTRL0_CS(chip, this)
		| BF_GPMI_CTRL0_LOCK_CS(LOCK_CS_ENABLE, this)
		| BF_GPMI_CTRL0_ADDRESS(address)
		| BF_GPMI_CTRL0_XFER_COUNT(geo->page_size);

	pio[1] = 0;
	pio[2] =  BM_GPMI_ECCCTRL_ENABLE_ECC
		| BF_GPMI_ECCCTRL_ECC_CMD(ecc_command)
		| BF_GPMI_ECCCTRL_BUFFER_MASK(buffer_mask);
	pio[3] = geo->page_size;
	pio[4] = payload;
	pio[5] = auxiliary;
	desc = dmaengine_prep_slave_sg(channel,
					(struct scatterlist *)pio,
					ARRAY_SIZE(pio), DMA_TRANS_NONE,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc)
		return -EINVAL;

	/* [3] Disable the BCH block */
	command_mode = BV_GPMI_CTRL0_COMMAND_MODE__WAIT_FOR_READY;
	address      = BV_GPMI_CTRL0_ADDRESS__NAND_DATA;

	pio[0] = BF_GPMI_CTRL0_COMMAND_MODE(command_mode)
		| BM_GPMI_CTRL0_WORD_LENGTH
		| BF_GPMI_CTRL0_CS(chip, this)
		| BF_GPMI_CTRL0_LOCK_CS(LOCK_CS_ENABLE, this)
		| BF_GPMI_CTRL0_ADDRESS(address)
		| BF_GPMI_CTRL0_XFER_COUNT(geo->page_size);
	pio[1] = 0;
	pio[2] = 0; /* clear GPMI_HW_GPMI_ECCCTRL, disable the BCH. */
	desc = dmaengine_prep_slave_sg(channel,
				(struct scatterlist *)pio, 3,
				DMA_TRANS_NONE,
				DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	if (!desc)
		return -EINVAL;

	/* [4] submit the DMA */
	return start_dma_with_bch_irq(this, desc);
}