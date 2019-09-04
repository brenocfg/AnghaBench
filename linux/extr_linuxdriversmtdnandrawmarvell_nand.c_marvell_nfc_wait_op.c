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
struct nand_chip {int /*<<< orphan*/  controller; } ;
struct marvell_nfc {int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned int IRQ_TIMEOUT ; 
 int /*<<< orphan*/  NDCR_RDYM ; 
 int NDSR_RDY (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  marvell_nfc_clear_int (struct marvell_nfc*,int) ; 
 int /*<<< orphan*/  marvell_nfc_disable_int (struct marvell_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvell_nfc_enable_int (struct marvell_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned int) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_nfc_wait_op(struct nand_chip *chip, unsigned int timeout_ms)
{
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	u32 pending;
	int ret;

	/* Timeout is expressed in ms */
	if (!timeout_ms)
		timeout_ms = IRQ_TIMEOUT;

	init_completion(&nfc->complete);

	marvell_nfc_enable_int(nfc, NDCR_RDYM);
	ret = wait_for_completion_timeout(&nfc->complete,
					  msecs_to_jiffies(timeout_ms));
	marvell_nfc_disable_int(nfc, NDCR_RDYM);
	pending = marvell_nfc_clear_int(nfc, NDSR_RDY(0) | NDSR_RDY(1));

	/*
	 * In case the interrupt was not served in the required time frame,
	 * check if the ISR was not served or if something went actually wrong.
	 */
	if (ret && !pending) {
		dev_err(nfc->dev, "Timeout waiting for RB signal\n");
		return -ETIMEDOUT;
	}

	return 0;
}