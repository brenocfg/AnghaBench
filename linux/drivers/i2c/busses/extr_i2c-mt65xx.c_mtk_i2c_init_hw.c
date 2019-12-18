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
typedef  int u16 ;
struct mtk_i2c {int timing_reg; int high_speed_reg; int ltiming_reg; scalar_t__ pdmabase; TYPE_1__* dev_comp; scalar_t__ have_pmic; scalar_t__ use_push_pull; } ;
struct TYPE_2__ {scalar_t__ dma_sync; scalar_t__ ltiming_adjust; scalar_t__ timing_adjust; scalar_t__ dcm; } ;

/* Variables and functions */
 int I2C_CONTROL_ACKERR_DET_EN ; 
 int I2C_CONTROL_ASYNC_MODE ; 
 int I2C_CONTROL_CLK_EXT_EN ; 
 int I2C_CONTROL_DMAACK_EN ; 
 int I2C_CONTROL_DMA_EN ; 
 int I2C_CONTROL_WRAPPER ; 
 int I2C_DCM_DISABLE ; 
 int I2C_DEFAULT_CLK_DIV ; 
 int I2C_DELAY_LEN ; 
 int /*<<< orphan*/  I2C_DMA_CLR_FLAG ; 
 int /*<<< orphan*/  I2C_DMA_HARD_RST ; 
 int I2C_IO_CONFIG_OPEN_DRAIN ; 
 int I2C_IO_CONFIG_PUSH_PULL ; 
 int I2C_SOFT_RST ; 
 int /*<<< orphan*/  OFFSET_CLOCK_DIV ; 
 int /*<<< orphan*/  OFFSET_CONTROL ; 
 int /*<<< orphan*/  OFFSET_DCM_EN ; 
 int /*<<< orphan*/  OFFSET_DELAY_LEN ; 
 int /*<<< orphan*/  OFFSET_HS ; 
 int /*<<< orphan*/  OFFSET_IO_CONFIG ; 
 int /*<<< orphan*/  OFFSET_LTIMING ; 
 int /*<<< orphan*/  OFFSET_PATH_DIR ; 
 scalar_t__ OFFSET_RST ; 
 int /*<<< orphan*/  OFFSET_SOFTRESET ; 
 int /*<<< orphan*/  OFFSET_TIMING ; 
 int /*<<< orphan*/  mtk_i2c_writew (struct mtk_i2c*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_i2c_init_hw(struct mtk_i2c *i2c)
{
	u16 control_reg;

	mtk_i2c_writew(i2c, I2C_SOFT_RST, OFFSET_SOFTRESET);

	/* Set ioconfig */
	if (i2c->use_push_pull)
		mtk_i2c_writew(i2c, I2C_IO_CONFIG_PUSH_PULL, OFFSET_IO_CONFIG);
	else
		mtk_i2c_writew(i2c, I2C_IO_CONFIG_OPEN_DRAIN, OFFSET_IO_CONFIG);

	if (i2c->dev_comp->dcm)
		mtk_i2c_writew(i2c, I2C_DCM_DISABLE, OFFSET_DCM_EN);

	if (i2c->dev_comp->timing_adjust)
		mtk_i2c_writew(i2c, I2C_DEFAULT_CLK_DIV - 1, OFFSET_CLOCK_DIV);

	mtk_i2c_writew(i2c, i2c->timing_reg, OFFSET_TIMING);
	mtk_i2c_writew(i2c, i2c->high_speed_reg, OFFSET_HS);
	if (i2c->dev_comp->ltiming_adjust)
		mtk_i2c_writew(i2c, i2c->ltiming_reg, OFFSET_LTIMING);

	/* If use i2c pin from PMIC mt6397 side, need set PATH_DIR first */
	if (i2c->have_pmic)
		mtk_i2c_writew(i2c, I2C_CONTROL_WRAPPER, OFFSET_PATH_DIR);

	control_reg = I2C_CONTROL_ACKERR_DET_EN |
		      I2C_CONTROL_CLK_EXT_EN | I2C_CONTROL_DMA_EN;
	if (i2c->dev_comp->dma_sync)
		control_reg |= I2C_CONTROL_DMAACK_EN | I2C_CONTROL_ASYNC_MODE;

	mtk_i2c_writew(i2c, control_reg, OFFSET_CONTROL);
	mtk_i2c_writew(i2c, I2C_DELAY_LEN, OFFSET_DELAY_LEN);

	writel(I2C_DMA_HARD_RST, i2c->pdmabase + OFFSET_RST);
	udelay(50);
	writel(I2C_DMA_CLR_FLAG, i2c->pdmabase + OFFSET_RST);
}