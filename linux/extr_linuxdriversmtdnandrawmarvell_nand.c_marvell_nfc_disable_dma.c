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
typedef  int u32 ;
struct marvell_nfc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ NDCR ; 
 int NDCR_DMA_EN ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void marvell_nfc_disable_dma(struct marvell_nfc *nfc)
{
	u32 reg;

	reg = readl_relaxed(nfc->regs + NDCR);
	writel_relaxed(reg & ~NDCR_DMA_EN, nfc->regs + NDCR);
}