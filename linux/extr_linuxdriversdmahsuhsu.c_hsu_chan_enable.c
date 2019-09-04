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
struct hsu_dma_chan {scalar_t__ direction; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  HSU_CH_CR ; 
 int /*<<< orphan*/  HSU_CH_CR_CHA ; 
 int /*<<< orphan*/  HSU_CH_CR_CHD ; 
 int /*<<< orphan*/  hsu_chan_writel (struct hsu_dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hsu_chan_enable(struct hsu_dma_chan *hsuc)
{
	u32 cr = HSU_CH_CR_CHA;

	if (hsuc->direction == DMA_MEM_TO_DEV)
		cr &= ~HSU_CH_CR_CHD;
	else if (hsuc->direction == DMA_DEV_TO_MEM)
		cr |= HSU_CH_CR_CHD;

	hsu_chan_writel(hsuc, HSU_CH_CR, cr);
}