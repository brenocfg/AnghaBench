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
 int /*<<< orphan*/  GENI_DMA_MODE_EN ; 
 scalar_t__ SE_GENI_DMA_MODE_EN ; 
 int /*<<< orphan*/  geni_se_irq_clear (struct geni_se*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void geni_se_select_dma_mode(struct geni_se *se)
{
	u32 val;

	geni_se_irq_clear(se);

	val = readl_relaxed(se->base + SE_GENI_DMA_MODE_EN);
	val |= GENI_DMA_MODE_EN;
	writel_relaxed(val, se->base + SE_GENI_DMA_MODE_EN);
}