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
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct marvell_nfc {scalar_t__ regs; scalar_t__ use_dma; scalar_t__ dma_chan; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ NDCR ; 
 int NDCR_DMA_EN ; 
 scalar_t__ NDSR ; 
 int /*<<< orphan*/  POLL_PERIOD ; 
 int /*<<< orphan*/  POLL_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int marvell_nfc_end_cmd(struct nand_chip *chip, int flag,
			       const char *label)
{
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 val;
	int ret;

	ret = readl_relaxed_poll_timeout(nfc->regs + NDSR, val,
					 val & flag,
					 POLL_PERIOD, POLL_TIMEOUT);

	if (ret) {
		dev_err(nfc->dev, "Timeout on %s (NDSR: 0x%08x)\n",
			label, val);
		if (nfc->dma_chan)
			dmaengine_terminate_all(nfc->dma_chan);
		return ret;
	}

	/*
	 * DMA function uses this helper to poll on CMDD bits without wanting
	 * them to be cleared.
	 */
	if (nfc->use_dma && (readl_relaxed(nfc->regs + NDCR) & NDCR_DMA_EN))
		return 0;

	writel_relaxed(flag, nfc->regs + NDSR);

	return 0;
}