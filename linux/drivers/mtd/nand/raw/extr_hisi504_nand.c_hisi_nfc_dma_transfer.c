#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mode; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {unsigned long oobsize; } ;
struct hinfc_host {unsigned long dma_buffer; unsigned long dma_oob; scalar_t__ command; int addr_cycle; int chipselect; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_complete; struct nand_chip chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINFC504_DMA_ADDR_DATA ; 
 int /*<<< orphan*/  HINFC504_DMA_ADDR_OOB ; 
 int /*<<< orphan*/  HINFC504_DMA_CTRL ; 
 int HINFC504_DMA_CTRL_ADDR_NUM_SHIFT ; 
 int HINFC504_DMA_CTRL_BURST16_EN ; 
 int HINFC504_DMA_CTRL_BURST4_EN ; 
 int HINFC504_DMA_CTRL_BURST8_EN ; 
 int HINFC504_DMA_CTRL_CS_MASK ; 
 int HINFC504_DMA_CTRL_CS_SHIFT ; 
 int HINFC504_DMA_CTRL_DATA_AREA_EN ; 
 int HINFC504_DMA_CTRL_DMA_START ; 
 int HINFC504_DMA_CTRL_OOB_AREA_EN ; 
 unsigned long HINFC504_DMA_CTRL_WE ; 
 int /*<<< orphan*/  HINFC504_DMA_LEN ; 
 unsigned long HINFC504_DMA_LEN_OOB_MASK ; 
 unsigned long HINFC504_DMA_LEN_OOB_SHIFT ; 
 int /*<<< orphan*/  HINFC504_DMA_PARA ; 
 unsigned long HINFC504_DMA_PARA_DATA_ECC_EN ; 
 unsigned long HINFC504_DMA_PARA_DATA_EDC_EN ; 
 unsigned long HINFC504_DMA_PARA_DATA_RW_EN ; 
 unsigned long HINFC504_DMA_PARA_OOB_ECC_EN ; 
 unsigned long HINFC504_DMA_PARA_OOB_EDC_EN ; 
 unsigned long HINFC504_DMA_PARA_OOB_RW_EN ; 
 int /*<<< orphan*/  HINFC504_NFC_DMA_TIMEOUT ; 
 scalar_t__ NAND_CMD_READOOB ; 
 scalar_t__ NAND_ECC_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long hinfc_read (struct hinfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinfc_write (struct hinfc_host*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_nfc_dma_transfer(struct hinfc_host *host, int todev)
{
	struct nand_chip *chip = &host->chip;
	struct mtd_info	*mtd = nand_to_mtd(chip);
	unsigned long val;
	int ret;

	hinfc_write(host, host->dma_buffer, HINFC504_DMA_ADDR_DATA);
	hinfc_write(host, host->dma_oob, HINFC504_DMA_ADDR_OOB);

	if (chip->ecc.mode == NAND_ECC_NONE) {
		hinfc_write(host, ((mtd->oobsize & HINFC504_DMA_LEN_OOB_MASK)
			<< HINFC504_DMA_LEN_OOB_SHIFT), HINFC504_DMA_LEN);

		hinfc_write(host, HINFC504_DMA_PARA_DATA_RW_EN
			| HINFC504_DMA_PARA_OOB_RW_EN, HINFC504_DMA_PARA);
	} else {
		if (host->command == NAND_CMD_READOOB)
			hinfc_write(host, HINFC504_DMA_PARA_OOB_RW_EN
			| HINFC504_DMA_PARA_OOB_EDC_EN
			| HINFC504_DMA_PARA_OOB_ECC_EN, HINFC504_DMA_PARA);
		else
			hinfc_write(host, HINFC504_DMA_PARA_DATA_RW_EN
			| HINFC504_DMA_PARA_OOB_RW_EN
			| HINFC504_DMA_PARA_DATA_EDC_EN
			| HINFC504_DMA_PARA_OOB_EDC_EN
			| HINFC504_DMA_PARA_DATA_ECC_EN
			| HINFC504_DMA_PARA_OOB_ECC_EN, HINFC504_DMA_PARA);

	}

	val = (HINFC504_DMA_CTRL_DMA_START | HINFC504_DMA_CTRL_BURST4_EN
		| HINFC504_DMA_CTRL_BURST8_EN | HINFC504_DMA_CTRL_BURST16_EN
		| HINFC504_DMA_CTRL_DATA_AREA_EN | HINFC504_DMA_CTRL_OOB_AREA_EN
		| ((host->addr_cycle == 4 ? 1 : 0)
			<< HINFC504_DMA_CTRL_ADDR_NUM_SHIFT)
		| ((host->chipselect & HINFC504_DMA_CTRL_CS_MASK)
			<< HINFC504_DMA_CTRL_CS_SHIFT));

	if (todev)
		val |= HINFC504_DMA_CTRL_WE;

	init_completion(&host->cmd_complete);

	hinfc_write(host, val, HINFC504_DMA_CTRL);
	ret = wait_for_completion_timeout(&host->cmd_complete,
			HINFC504_NFC_DMA_TIMEOUT);

	if (!ret) {
		dev_err(host->dev, "DMA operation(irq) timeout!\n");
		/* sanity check */
		val = hinfc_read(host, HINFC504_DMA_CTRL);
		if (!(val & HINFC504_DMA_CTRL_DMA_START))
			dev_err(host->dev, "DMA is already done but without irq ACK!\n");
		else
			dev_err(host->dev, "DMA is really timeout!\n");
	}
}