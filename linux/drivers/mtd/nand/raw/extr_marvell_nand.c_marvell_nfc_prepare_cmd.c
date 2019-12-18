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
 int ETIMEDOUT ; 
 scalar_t__ NDCR ; 
 int NDCR_ND_RUN ; 
 scalar_t__ NDSR ; 
 int NDSR_WRCMDREQ ; 
 int /*<<< orphan*/  POLL_PERIOD ; 
 int /*<<< orphan*/  POLL_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int marvell_nfc_wait_ndrun (struct nand_chip*) ; 
 int readl (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int marvell_nfc_prepare_cmd(struct nand_chip *chip)
{
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 ndcr, val;
	int ret;

	/* Poll ND_RUN and clear NDSR before issuing any command */
	ret = marvell_nfc_wait_ndrun(chip);
	if (ret) {
		dev_err(nfc->dev, "Last operation did not succeed\n");
		return ret;
	}

	ndcr = readl_relaxed(nfc->regs + NDCR);
	writel_relaxed(readl(nfc->regs + NDSR), nfc->regs + NDSR);

	/* Assert ND_RUN bit and wait the NFC to be ready */
	writel_relaxed(ndcr | NDCR_ND_RUN, nfc->regs + NDCR);
	ret = readl_relaxed_poll_timeout(nfc->regs + NDSR, val,
					 val & NDSR_WRCMDREQ,
					 POLL_PERIOD, POLL_TIMEOUT);
	if (ret) {
		dev_err(nfc->dev, "Timeout on WRCMDRE\n");
		return -ETIMEDOUT;
	}

	/* Command may be written, clear WRCMDREQ status bit */
	writel_relaxed(NDSR_WRCMDREQ, nfc->regs + NDSR);

	return 0;
}