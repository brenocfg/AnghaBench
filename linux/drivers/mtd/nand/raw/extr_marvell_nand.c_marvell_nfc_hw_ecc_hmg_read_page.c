#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  cur_cs; } ;
struct marvell_hw_ecc_layout {unsigned int data_bytes; unsigned int spare_bytes; unsigned int ecc_bytes; } ;
struct TYPE_2__ {struct marvell_hw_ecc_layout* layout; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvell_nfc_check_empty_chunk (struct nand_chip*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  marvell_nfc_disable_hw_ecc (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_enable_hw_ecc (struct nand_chip*) ; 
 int marvell_nfc_hw_ecc_correct (struct nand_chip*,int*) ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_hmg_do_read_page (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  marvell_nfc_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_marvell_nand (struct nand_chip*) ; 

__attribute__((used)) static int marvell_nfc_hw_ecc_hmg_read_page(struct nand_chip *chip, u8 *buf,
					    int oob_required, int page)
{
	const struct marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	unsigned int full_sz = lt->data_bytes + lt->spare_bytes + lt->ecc_bytes;
	int max_bitflips = 0, ret;
	u8 *raw_buf;

	marvell_nfc_select_target(chip, chip->cur_cs);
	marvell_nfc_enable_hw_ecc(chip);
	marvell_nfc_hw_ecc_hmg_do_read_page(chip, buf, chip->oob_poi, false,
					    page);
	ret = marvell_nfc_hw_ecc_correct(chip, &max_bitflips);
	marvell_nfc_disable_hw_ecc(chip);

	if (!ret)
		return max_bitflips;

	/*
	 * When ECC failures are detected, check if the full page has been
	 * written or not. Ignore the failure if it is actually empty.
	 */
	raw_buf = kmalloc(full_sz, GFP_KERNEL);
	if (!raw_buf)
		return -ENOMEM;

	marvell_nfc_hw_ecc_hmg_do_read_page(chip, raw_buf, raw_buf +
					    lt->data_bytes, true, page);
	marvell_nfc_check_empty_chunk(chip, raw_buf, full_sz, NULL, 0, NULL, 0,
				      &max_bitflips);
	kfree(raw_buf);

	return max_bitflips;
}