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
struct mtd_info {int dummy; } ;
struct mpc5121_nfc_prv {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_CONFIG1 ; 
 int /*<<< orphan*/  NFC_CONFIG2 ; 
 int NFC_INT ; 
 int NFC_INT_MASK ; 
 int /*<<< orphan*/  NFC_TIMEOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mpc5121_nfc_prv* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nfc_clear (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 int nfc_read (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc5121_nfc_done(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mpc5121_nfc_prv *prv = nand_get_controller_data(chip);
	int rv;

	if ((nfc_read(mtd, NFC_CONFIG2) & NFC_INT) == 0) {
		nfc_clear(mtd, NFC_CONFIG1, NFC_INT_MASK);
		rv = wait_event_timeout(prv->irq_waitq,
			(nfc_read(mtd, NFC_CONFIG2) & NFC_INT), NFC_TIMEOUT);

		if (!rv)
			dev_warn(prv->dev,
				"Timeout while waiting for interrupt.\n");
	}

	nfc_clear(mtd, NFC_CONFIG2, NFC_INT);
}