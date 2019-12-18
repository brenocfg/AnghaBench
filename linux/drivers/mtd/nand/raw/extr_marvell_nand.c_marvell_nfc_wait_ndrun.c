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
struct marvell_nfc {scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ NDCR ; 
 int NDCR_ND_RUN ; 
 int /*<<< orphan*/  POLL_PERIOD ; 
 int /*<<< orphan*/  POLL_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int marvell_nfc_wait_ndrun(struct nand_chip *chip)
{
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 val;
	int ret;

	/*
	 * The command is being processed, wait for the ND_RUN bit to be
	 * cleared by the NFC. If not, we must clear it by hand.
	 */
	ret = readl_relaxed_poll_timeout(nfc->regs + NDCR, val,
					 (val & NDCR_ND_RUN) == 0,
					 POLL_PERIOD, POLL_TIMEOUT);
	if (ret) {
		dev_err(nfc->dev, "Timeout on NAND controller run mode\n");
		writel_relaxed(readl(nfc->regs + NDCR) & ~NDCR_ND_RUN,
			       nfc->regs + NDCR);
		return ret;
	}

	return 0;
}