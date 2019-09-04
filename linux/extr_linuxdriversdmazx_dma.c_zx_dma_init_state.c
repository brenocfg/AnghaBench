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
struct zx_dma_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ REG_ZX_CFG_ERR_IRQ_RAW ; 
 scalar_t__ REG_ZX_DMA_ARB ; 
 scalar_t__ REG_ZX_DST_ERR_IRQ_RAW ; 
 scalar_t__ REG_ZX_SRC_ERR_IRQ_RAW ; 
 scalar_t__ REG_ZX_TC_IRQ_RAW ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void zx_dma_init_state(struct zx_dma_dev *d)
{
	/* set same priority */
	writel_relaxed(0x0, d->base + REG_ZX_DMA_ARB);
	/* clear all irq */
	writel_relaxed(0xffffffff, d->base + REG_ZX_TC_IRQ_RAW);
	writel_relaxed(0xffffffff, d->base + REG_ZX_SRC_ERR_IRQ_RAW);
	writel_relaxed(0xffffffff, d->base + REG_ZX_DST_ERR_IRQ_RAW);
	writel_relaxed(0xffffffff, d->base + REG_ZX_CFG_ERR_IRQ_RAW);
}