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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct spi_nor {int addr_width; int read_dummy; int /*<<< orphan*/  program_opcode; int /*<<< orphan*/  read_opcode; int /*<<< orphan*/  write_proto; int /*<<< orphan*/  read_proto; struct hifmc_priv* priv; } ;
struct hifmc_priv {int /*<<< orphan*/  chipselect; struct hifmc_host* host; } ;
struct hifmc_host {scalar_t__ regbase; } ;
typedef  int loff_t ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ FMC_ADDRL ; 
 scalar_t__ FMC_CFG ; 
 int FMC_CFG_OP_MODE_MASK ; 
 int FMC_CFG_OP_MODE_NORMAL ; 
 scalar_t__ FMC_DMA_LEN ; 
 int FMC_DMA_LEN_SET (size_t) ; 
 scalar_t__ FMC_DMA_SADDR_D0 ; 
 scalar_t__ FMC_INT_CLR ; 
 scalar_t__ FMC_OP_CFG ; 
 scalar_t__ FMC_OP_DMA ; 
 scalar_t__ FMC_OP_READ ; 
 int OP_CFG_DUMMY_NUM (int) ; 
 int OP_CFG_FM_CS (int /*<<< orphan*/ ) ; 
 int OP_CFG_MEM_IF_TYPE (scalar_t__) ; 
 int OP_CTRL_DMA_OP_READY ; 
 int OP_CTRL_RD_OPCODE (int /*<<< orphan*/ ) ; 
 int OP_CTRL_RW_OP (scalar_t__) ; 
 int OP_CTRL_WR_OPCODE (int /*<<< orphan*/ ) ; 
 int SPI_NOR_ADDR_MODE_3BYTES ; 
 int SPI_NOR_ADDR_MODE_4BYTES ; 
 int SPI_NOR_ADDR_MODE_MASK ; 
 scalar_t__ hisi_spi_nor_get_if_type (int /*<<< orphan*/ ) ; 
 int hisi_spi_nor_wait_op_finish (struct hifmc_host*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hisi_spi_nor_dma_transfer(struct spi_nor *nor, loff_t start_off,
		dma_addr_t dma_buf, size_t len, u8 op_type)
{
	struct hifmc_priv *priv = nor->priv;
	struct hifmc_host *host = priv->host;
	u8 if_type = 0;
	u32 reg;

	reg = readl(host->regbase + FMC_CFG);
	reg &= ~(FMC_CFG_OP_MODE_MASK | SPI_NOR_ADDR_MODE_MASK);
	reg |= FMC_CFG_OP_MODE_NORMAL;
	reg |= (nor->addr_width == 4) ? SPI_NOR_ADDR_MODE_4BYTES
		: SPI_NOR_ADDR_MODE_3BYTES;
	writel(reg, host->regbase + FMC_CFG);

	writel(start_off, host->regbase + FMC_ADDRL);
	writel(dma_buf, host->regbase + FMC_DMA_SADDR_D0);
	writel(FMC_DMA_LEN_SET(len), host->regbase + FMC_DMA_LEN);

	reg = OP_CFG_FM_CS(priv->chipselect);
	if (op_type == FMC_OP_READ)
		if_type = hisi_spi_nor_get_if_type(nor->read_proto);
	else
		if_type = hisi_spi_nor_get_if_type(nor->write_proto);
	reg |= OP_CFG_MEM_IF_TYPE(if_type);
	if (op_type == FMC_OP_READ)
		reg |= OP_CFG_DUMMY_NUM(nor->read_dummy >> 3);
	writel(reg, host->regbase + FMC_OP_CFG);

	writel(0xff, host->regbase + FMC_INT_CLR);
	reg = OP_CTRL_RW_OP(op_type) | OP_CTRL_DMA_OP_READY;
	reg |= (op_type == FMC_OP_READ)
		? OP_CTRL_RD_OPCODE(nor->read_opcode)
		: OP_CTRL_WR_OPCODE(nor->program_opcode);
	writel(reg, host->regbase + FMC_OP_DMA);

	return hisi_spi_nor_wait_op_finish(host);
}