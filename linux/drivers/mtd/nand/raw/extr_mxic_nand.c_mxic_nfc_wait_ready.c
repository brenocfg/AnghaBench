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
struct nand_chip {int dummy; } ;
struct mxic_nand_ctlr {int /*<<< orphan*/  dev; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IRQ_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct mxic_nand_ctlr* nand_get_controller_data (struct nand_chip*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int  mxic_nfc_wait_ready(struct nand_chip *chip)
{
	struct mxic_nand_ctlr *nfc = nand_get_controller_data(chip);
	int ret;

	ret = wait_for_completion_timeout(&nfc->complete,
					  msecs_to_jiffies(IRQ_TIMEOUT));
	if (!ret) {
		dev_err(nfc->dev, "nand device timeout\n");
		return -ETIMEDOUT;
	}

	return 0;
}