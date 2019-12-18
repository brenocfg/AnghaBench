#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  tPROG_max; } ;
struct TYPE_6__ {TYPE_1__ sdr; } ;
struct TYPE_7__ {TYPE_2__ timings; } ;
struct nand_chip {TYPE_3__ data_interface; int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  cur_cs; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;
struct marvell_hw_ecc_layout {int data_bytes; int spare_bytes; int nchunks; int full_chunk_cnt; int last_data_bytes; int last_spare_bytes; } ;
struct TYPE_8__ {struct marvell_hw_ecc_layout* layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSEC_TO_MSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvell_nfc_disable_hw_ecc (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_enable_hw_ecc (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_write_chunk (struct nand_chip*,int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  marvell_nfc_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  marvell_nfc_wait_ndrun (struct nand_chip*) ; 
 int marvell_nfc_wait_op (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 TYPE_4__* to_marvell_nand (struct nand_chip*) ; 

__attribute__((used)) static int marvell_nfc_hw_ecc_bch_write_page(struct nand_chip *chip,
					     const u8 *buf,
					     int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const struct marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	const u8 *data = buf;
	const u8 *spare = chip->oob_poi;
	int data_len = lt->data_bytes;
	int spare_len = lt->spare_bytes;
	int chunk, ret;

	marvell_nfc_select_target(chip, chip->cur_cs);

	/* Spare data will be written anyway, so clear it to avoid garbage */
	if (!oob_required)
		memset(chip->oob_poi, 0xFF, mtd->oobsize);

	marvell_nfc_enable_hw_ecc(chip);

	for (chunk = 0; chunk < lt->nchunks; chunk++) {
		if (chunk >= lt->full_chunk_cnt) {
			data_len = lt->last_data_bytes;
			spare_len = lt->last_spare_bytes;
		}

		marvell_nfc_hw_ecc_bch_write_chunk(chip, chunk, data, data_len,
						   spare, spare_len, page);
		data += data_len;
		spare += spare_len;

		/*
		 * Waiting only for CMDD or PAGED is not enough, ECC are
		 * partially written. No flag is set once the operation is
		 * really finished but the ND_RUN bit is cleared, so wait for it
		 * before stepping into the next command.
		 */
		marvell_nfc_wait_ndrun(chip);
	}

	ret = marvell_nfc_wait_op(chip,
				  PSEC_TO_MSEC(chip->data_interface.timings.sdr.tPROG_max));

	marvell_nfc_disable_hw_ecc(chip);

	if (ret)
		return ret;

	return 0;
}