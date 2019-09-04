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
typedef  int u8 ;
typedef  int u32 ;
struct spi_nor {struct hifmc_priv* priv; } ;
struct hifmc_priv {int /*<<< orphan*/  chipselect; struct hifmc_host* host; } ;
struct hifmc_host {scalar_t__ regbase; } ;

/* Variables and functions */
 scalar_t__ FMC_CMD ; 
 int FMC_CMD_CMD1 (int) ; 
 scalar_t__ FMC_DATA_NUM ; 
 int FMC_DATA_NUM_CNT (int) ; 
 scalar_t__ FMC_INT_CLR ; 
 scalar_t__ FMC_OP ; 
 scalar_t__ FMC_OP_CFG ; 
 int FMC_OP_CMD1_EN ; 
 int FMC_OP_REG_OP_START ; 
 int OP_CFG_FM_CS (int /*<<< orphan*/ ) ; 
 int hisi_spi_nor_wait_op_finish (struct hifmc_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int hisi_spi_nor_op_reg(struct spi_nor *nor,
				u8 opcode, int len, u8 optype)
{
	struct hifmc_priv *priv = nor->priv;
	struct hifmc_host *host = priv->host;
	u32 reg;

	reg = FMC_CMD_CMD1(opcode);
	writel(reg, host->regbase + FMC_CMD);

	reg = FMC_DATA_NUM_CNT(len);
	writel(reg, host->regbase + FMC_DATA_NUM);

	reg = OP_CFG_FM_CS(priv->chipselect);
	writel(reg, host->regbase + FMC_OP_CFG);

	writel(0xff, host->regbase + FMC_INT_CLR);
	reg = FMC_OP_CMD1_EN | FMC_OP_REG_OP_START | optype;
	writel(reg, host->regbase + FMC_OP);

	return hisi_spi_nor_wait_op_finish(host);
}