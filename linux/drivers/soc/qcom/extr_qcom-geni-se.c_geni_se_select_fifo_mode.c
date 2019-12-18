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
typedef  scalar_t__ u32 ;
struct geni_se {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ GENI_DMA_MODE_EN ; 
 scalar_t__ GENI_SE_UART ; 
 scalar_t__ M_CMD_DONE_EN ; 
 scalar_t__ M_RX_FIFO_LAST_EN ; 
 scalar_t__ M_RX_FIFO_WATERMARK_EN ; 
 scalar_t__ M_TX_FIFO_WATERMARK_EN ; 
 scalar_t__ SE_GENI_DMA_MODE_EN ; 
 scalar_t__ SE_GENI_M_IRQ_EN ; 
 scalar_t__ SE_GENI_S_IRQ_EN ; 
 scalar_t__ S_CMD_DONE_EN ; 
 int /*<<< orphan*/  geni_se_irq_clear (struct geni_se*) ; 
 scalar_t__ geni_se_read_proto (struct geni_se*) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void geni_se_select_fifo_mode(struct geni_se *se)
{
	u32 proto = geni_se_read_proto(se);
	u32 val;

	geni_se_irq_clear(se);

	val = readl_relaxed(se->base + SE_GENI_M_IRQ_EN);
	if (proto != GENI_SE_UART) {
		val |= M_CMD_DONE_EN | M_TX_FIFO_WATERMARK_EN;
		val |= M_RX_FIFO_WATERMARK_EN | M_RX_FIFO_LAST_EN;
	}
	writel_relaxed(val, se->base + SE_GENI_M_IRQ_EN);

	val = readl_relaxed(se->base + SE_GENI_S_IRQ_EN);
	if (proto != GENI_SE_UART)
		val |= S_CMD_DONE_EN;
	writel_relaxed(val, se->base + SE_GENI_S_IRQ_EN);

	val = readl_relaxed(se->base + SE_GENI_DMA_MODE_EN);
	val &= ~GENI_DMA_MODE_EN;
	writel_relaxed(val, se->base + SE_GENI_DMA_MODE_EN);
}