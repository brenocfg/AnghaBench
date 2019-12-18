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
struct mxs_ssp {scalar_t__ base; } ;
struct mxs_mmc_host {scalar_t__ sdio_irq_en; struct mxs_ssp ssp; } ;

/* Variables and functions */
 int BF_SSP (int,int /*<<< orphan*/ ) ; 
 int BM_SSP_CTRL0_IGNORE_CRC ; 
 int BM_SSP_CTRL0_SDIO_IRQ_CHECK ; 
 int BM_SSP_CTRL1_DATA_CRC_IRQ_EN ; 
 int BM_SSP_CTRL1_DATA_TIMEOUT_IRQ_EN ; 
 int BM_SSP_CTRL1_DMA_ENABLE ; 
 int BM_SSP_CTRL1_POLARITY ; 
 int BM_SSP_CTRL1_RECV_TIMEOUT_IRQ_EN ; 
 int BM_SSP_CTRL1_RESP_ERR_IRQ_EN ; 
 int BM_SSP_CTRL1_RESP_TIMEOUT_IRQ_EN ; 
 int BM_SSP_CTRL1_SDIO_IRQ_EN ; 
 int /*<<< orphan*/  CTRL1_SSP_MODE ; 
 int /*<<< orphan*/  CTRL1_WORD_LENGTH ; 
 scalar_t__ HW_SSP_CTRL0 ; 
 scalar_t__ HW_SSP_CTRL1 (struct mxs_ssp*) ; 
 scalar_t__ HW_SSP_TIMING (struct mxs_ssp*) ; 
 int /*<<< orphan*/  TIMING_CLOCK_DIVIDE ; 
 int /*<<< orphan*/  TIMING_CLOCK_RATE ; 
 int /*<<< orphan*/  TIMING_TIMEOUT ; 
 int stmp_reset_block (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxs_mmc_reset(struct mxs_mmc_host *host)
{
	struct mxs_ssp *ssp = &host->ssp;
	u32 ctrl0, ctrl1;
	int ret;

	ret = stmp_reset_block(ssp->base);
	if (ret)
		return ret;

	ctrl0 = BM_SSP_CTRL0_IGNORE_CRC;
	ctrl1 = BF_SSP(0x3, CTRL1_SSP_MODE) |
		BF_SSP(0x7, CTRL1_WORD_LENGTH) |
		BM_SSP_CTRL1_DMA_ENABLE |
		BM_SSP_CTRL1_POLARITY |
		BM_SSP_CTRL1_RECV_TIMEOUT_IRQ_EN |
		BM_SSP_CTRL1_DATA_CRC_IRQ_EN |
		BM_SSP_CTRL1_DATA_TIMEOUT_IRQ_EN |
		BM_SSP_CTRL1_RESP_TIMEOUT_IRQ_EN |
		BM_SSP_CTRL1_RESP_ERR_IRQ_EN;

	writel(BF_SSP(0xffff, TIMING_TIMEOUT) |
	       BF_SSP(2, TIMING_CLOCK_DIVIDE) |
	       BF_SSP(0, TIMING_CLOCK_RATE),
	       ssp->base + HW_SSP_TIMING(ssp));

	if (host->sdio_irq_en) {
		ctrl0 |= BM_SSP_CTRL0_SDIO_IRQ_CHECK;
		ctrl1 |= BM_SSP_CTRL1_SDIO_IRQ_EN;
	}

	writel(ctrl0, ssp->base + HW_SSP_CTRL0);
	writel(ctrl1, ssp->base + HW_SSP_CTRL1(ssp));
	return 0;
}