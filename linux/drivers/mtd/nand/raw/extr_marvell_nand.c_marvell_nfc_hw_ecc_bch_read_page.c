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
typedef  int u32 ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  cur_cs; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;
struct marvell_hw_ecc_layout {int data_bytes; int spare_bytes; int nchunks; int full_chunk_cnt; int last_data_bytes; int last_spare_bytes; int ecc_bytes; int last_ecc_bytes; int writesize; int strength; } ;
struct TYPE_2__ {struct marvell_hw_ecc_layout* layout; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  marvell_nfc_check_empty_chunk (struct nand_chip*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  marvell_nfc_disable_hw_ecc (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_enable_hw_ecc (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_read_chunk (struct nand_chip*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int marvell_nfc_hw_ecc_correct (struct nand_chip*,int*) ; 
 int /*<<< orphan*/  marvell_nfc_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_change_read_column_op (struct nand_chip*,int,int /*<<< orphan*/ *,int,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 TYPE_1__* to_marvell_nand (struct nand_chip*) ; 

__attribute__((used)) static int marvell_nfc_hw_ecc_bch_read_page(struct nand_chip *chip,
					    u8 *buf, int oob_required,
					    int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const struct marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	int data_len = lt->data_bytes, spare_len = lt->spare_bytes;
	u8 *data = buf, *spare = chip->oob_poi;
	int max_bitflips = 0;
	u32 failure_mask = 0;
	int chunk, ret;

	marvell_nfc_select_target(chip, chip->cur_cs);

	/*
	 * With BCH, OOB is not fully used (and thus not read entirely), not
	 * expected bytes could show up at the end of the OOB buffer if not
	 * explicitly erased.
	 */
	if (oob_required)
		memset(chip->oob_poi, 0xFF, mtd->oobsize);

	marvell_nfc_enable_hw_ecc(chip);

	for (chunk = 0; chunk < lt->nchunks; chunk++) {
		/* Update length for the last chunk */
		if (chunk >= lt->full_chunk_cnt) {
			data_len = lt->last_data_bytes;
			spare_len = lt->last_spare_bytes;
		}

		/* Read the chunk and detect number of bitflips */
		marvell_nfc_hw_ecc_bch_read_chunk(chip, chunk, data, data_len,
						  spare, spare_len, page);
		ret = marvell_nfc_hw_ecc_correct(chip, &max_bitflips);
		if (ret)
			failure_mask |= BIT(chunk);

		data += data_len;
		spare += spare_len;
	}

	marvell_nfc_disable_hw_ecc(chip);

	if (!failure_mask)
		return max_bitflips;

	/*
	 * Please note that dumping the ECC bytes during a normal read with OOB
	 * area would add a significant overhead as ECC bytes are "consumed" by
	 * the controller in normal mode and must be re-read in raw mode. To
	 * avoid dropping the performances, we prefer not to include them. The
	 * user should re-read the page in raw mode if ECC bytes are required.
	 */

	/*
	 * In case there is any subpage read error reported by ->correct(), we
	 * usually re-read only ECC bytes in raw mode and check if the whole
	 * page is empty. In this case, it is normal that the ECC check failed
	 * and we just ignore the error.
	 *
	 * However, it has been empirically observed that for some layouts (e.g
	 * 2k page, 8b strength per 512B chunk), the controller tries to correct
	 * bits and may create itself bitflips in the erased area. To overcome
	 * this strange behavior, the whole page is re-read in raw mode, not
	 * only the ECC bytes.
	 */
	for (chunk = 0; chunk < lt->nchunks; chunk++) {
		int data_off_in_page, spare_off_in_page, ecc_off_in_page;
		int data_off, spare_off, ecc_off;
		int data_len, spare_len, ecc_len;

		/* No failure reported for this chunk, move to the next one */
		if (!(failure_mask & BIT(chunk)))
			continue;

		data_off_in_page = chunk * (lt->data_bytes + lt->spare_bytes +
					    lt->ecc_bytes);
		spare_off_in_page = data_off_in_page +
			(chunk < lt->full_chunk_cnt ? lt->data_bytes :
						      lt->last_data_bytes);
		ecc_off_in_page = spare_off_in_page +
			(chunk < lt->full_chunk_cnt ? lt->spare_bytes :
						      lt->last_spare_bytes);

		data_off = chunk * lt->data_bytes;
		spare_off = chunk * lt->spare_bytes;
		ecc_off = (lt->full_chunk_cnt * lt->spare_bytes) +
			  lt->last_spare_bytes +
			  (chunk * (lt->ecc_bytes + 2));

		data_len = chunk < lt->full_chunk_cnt ? lt->data_bytes :
							lt->last_data_bytes;
		spare_len = chunk < lt->full_chunk_cnt ? lt->spare_bytes :
							 lt->last_spare_bytes;
		ecc_len = chunk < lt->full_chunk_cnt ? lt->ecc_bytes :
						       lt->last_ecc_bytes;

		/*
		 * Only re-read the ECC bytes, unless we are using the 2k/8b
		 * layout which is buggy in the sense that the ECC engine will
		 * try to correct data bytes anyway, creating bitflips. In this
		 * case, re-read the entire page.
		 */
		if (lt->writesize == 2048 && lt->strength == 8) {
			nand_change_read_column_op(chip, data_off_in_page,
						   buf + data_off, data_len,
						   false);
			nand_change_read_column_op(chip, spare_off_in_page,
						   chip->oob_poi + spare_off, spare_len,
						   false);
		}

		nand_change_read_column_op(chip, ecc_off_in_page,
					   chip->oob_poi + ecc_off, ecc_len,
					   false);

		/* Check the entire chunk (data + spare + ecc) for emptyness */
		marvell_nfc_check_empty_chunk(chip, buf + data_off, data_len,
					      chip->oob_poi + spare_off, spare_len,
					      chip->oob_poi + ecc_off, ecc_len,
					      &max_bitflips);
	}

	return max_bitflips;
}