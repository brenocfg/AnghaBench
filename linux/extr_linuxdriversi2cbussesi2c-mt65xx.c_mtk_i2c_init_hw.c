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
struct mtk_i2c {int timing_reg; int high_speed_reg; scalar_t__ pdmabase; scalar_t__ base; scalar_t__ have_pmic; TYPE_1__* dev_comp; scalar_t__ use_push_pull; } ;
struct TYPE_2__ {scalar_t__ timing_adjust; scalar_t__ dcm; } ;

/* Variables and functions */
 int I2C_CONTROL_ACKERR_DET_EN ; 
 int I2C_CONTROL_CLK_EXT_EN ; 
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
 scalar_t__ OFFSET_CLOCK_DIV ; 
 scalar_t__ OFFSET_CONTROL ; 
 scalar_t__ OFFSET_DCM_EN ; 
 scalar_t__ OFFSET_DELAY_LEN ; 
 scalar_t__ OFFSET_HS ; 
 scalar_t__ OFFSET_IO_CONFIG ; 
 scalar_t__ OFFSET_PATH_DIR ; 
 scalar_t__ OFFSET_RST ; 
 scalar_t__ OFFSET_SOFTRESET ; 
 scalar_t__ OFFSET_TIMING ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void mtk_i2c_init_hw(struct mtk_i2c *i2c)
{
	u16 control_reg;

	writew(I2C_SOFT_RST, i2c->base + OFFSET_SOFTRESET);

	/* Set ioconfig */
	if (i2c->use_push_pull)
		writew(I2C_IO_CONFIG_PUSH_PULL, i2c->base + OFFSET_IO_CONFIG);
	else
		writew(I2C_IO_CONFIG_OPEN_DRAIN, i2c->base + OFFSET_IO_CONFIG);

	if (i2c->dev_comp->dcm)
		writew(I2C_DCM_DISABLE, i2c->base + OFFSET_DCM_EN);

	if (i2c->dev_comp->timing_adjust)
		writew(I2C_DEFAULT_CLK_DIV - 1, i2c->base + OFFSET_CLOCK_DIV);

	writew(i2c->timing_reg, i2c->base + OFFSET_TIMING);
	writew(i2c->high_speed_reg, i2c->base + OFFSET_HS);

	/* If use i2c pin from PMIC mt6397 side, need set PATH_DIR first */
	if (i2c->have_pmic)
		writew(I2C_CONTROL_WRAPPER, i2c->base + OFFSET_PATH_DIR);

	control_reg = I2C_CONTROL_ACKERR_DET_EN |
		      I2C_CONTROL_CLK_EXT_EN | I2C_CONTROL_DMA_EN;
	writew(control_reg, i2c->base + OFFSET_CONTROL);
	writew(I2C_DELAY_LEN, i2c->base + OFFSET_DELAY_LEN);

	writel(I2C_DMA_HARD_RST, i2c->pdmabase + OFFSET_RST);
	udelay(50);
	writel(I2C_DMA_CLR_FLAG, i2c->pdmabase + OFFSET_RST);
}