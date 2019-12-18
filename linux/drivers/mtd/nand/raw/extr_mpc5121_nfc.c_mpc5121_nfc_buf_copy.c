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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u_char ;
struct nand_chip {int dummy; } ;
struct mtd_info {scalar_t__ writesize; } ;
struct mpc5121_nfc_prv {scalar_t__ column; scalar_t__ regs; scalar_t__ spareonly; } ;

/* Variables and functions */
 scalar_t__ NFC_MAIN_AREA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mpc5121_nfc_copy_spare (struct mtd_info*,scalar_t__,int /*<<< orphan*/ *,int,int) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct mpc5121_nfc_prv* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void mpc5121_nfc_buf_copy(struct mtd_info *mtd, u_char *buf, int len,
									int wr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mpc5121_nfc_prv *prv = nand_get_controller_data(chip);
	uint c = prv->column;
	uint l;

	/* Handle spare area access */
	if (prv->spareonly || c >= mtd->writesize) {
		/* Calculate offset from beginning of spare area */
		if (c >= mtd->writesize)
			c -= mtd->writesize;

		prv->column += len;
		mpc5121_nfc_copy_spare(mtd, c, buf, len, wr);
		return;
	}

	/*
	 * Handle main area access - limit copy length to prevent
	 * crossing main/spare boundary.
	 */
	l = min((uint)len, mtd->writesize - c);
	prv->column += l;

	if (wr)
		memcpy_toio(prv->regs + NFC_MAIN_AREA(0) + c, buf, l);
	else
		memcpy_fromio(buf, prv->regs + NFC_MAIN_AREA(0) + c, l);

	/* Handle crossing main/spare boundary */
	if (l != len) {
		buf += l;
		len -= l;
		mpc5121_nfc_buf_copy(mtd, buf, len, wr);
	}
}