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
struct geni_se {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_COMMON_GENI_M_IRQ_EN ; 
 scalar_t__ SE_GENI_M_IRQ_EN ; 
 scalar_t__ SE_GENI_RX_RFR_WATERMARK_REG ; 
 scalar_t__ SE_GENI_RX_WATERMARK_REG ; 
 scalar_t__ SE_GENI_S_IRQ_EN ; 
 int /*<<< orphan*/  S_COMMON_GENI_S_IRQ_EN ; 
 int /*<<< orphan*/  geni_se_io_init (scalar_t__) ; 
 int /*<<< orphan*/  geni_se_io_set_mode (scalar_t__) ; 
 int /*<<< orphan*/  geni_se_irq_clear (struct geni_se*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void geni_se_init(struct geni_se *se, u32 rx_wm, u32 rx_rfr)
{
	u32 val;

	geni_se_irq_clear(se);
	geni_se_io_init(se->base);
	geni_se_io_set_mode(se->base);

	writel_relaxed(rx_wm, se->base + SE_GENI_RX_WATERMARK_REG);
	writel_relaxed(rx_rfr, se->base + SE_GENI_RX_RFR_WATERMARK_REG);

	val = readl_relaxed(se->base + SE_GENI_M_IRQ_EN);
	val |= M_COMMON_GENI_M_IRQ_EN;
	writel_relaxed(val, se->base + SE_GENI_M_IRQ_EN);

	val = readl_relaxed(se->base + SE_GENI_S_IRQ_EN);
	val |= S_COMMON_GENI_S_IRQ_EN;
	writel_relaxed(val, se->base + SE_GENI_S_IRQ_EN);
}