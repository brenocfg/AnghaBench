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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_spi_slave {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_DMA_EN ; 
 scalar_t__ SPIS_DMA_CFG_REG ; 
 int /*<<< orphan*/  TX_DMA_EN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_spi_slave_disable_dma(struct mtk_spi_slave *mdata)
{
	u32 reg_val;

	reg_val = readl(mdata->base + SPIS_DMA_CFG_REG);
	reg_val &= ~RX_DMA_EN;
	reg_val &= ~TX_DMA_EN;
	writel(reg_val, mdata->base + SPIS_DMA_CFG_REG);
}