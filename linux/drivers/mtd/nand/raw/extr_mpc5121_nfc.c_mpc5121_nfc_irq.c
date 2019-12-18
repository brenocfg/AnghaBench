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
struct mpc5121_nfc_prv {int /*<<< orphan*/  irq_waitq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  NFC_CONFIG1 ; 
 int /*<<< orphan*/  NFC_INT_MASK ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mpc5121_nfc_prv* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  nfc_set (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mpc5121_nfc_irq(int irq, void *data)
{
	struct mtd_info *mtd = data;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mpc5121_nfc_prv *prv = nand_get_controller_data(chip);

	nfc_set(mtd, NFC_CONFIG1, NFC_INT_MASK);
	wake_up(&prv->irq_waitq);

	return IRQ_HANDLED;
}