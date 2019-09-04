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
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;
struct marvell_hw_ecc_layout {int data_bytes; int spare_bytes; int nchunks; int full_chunk_cnt; int last_data_bytes; int last_spare_bytes; int ecc_bytes; int last_ecc_bytes; } ;
struct TYPE_2__ {struct marvell_hw_ecc_layout* layout; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int BIT (int) ; 
 int /*<<< orphan*/  marvell_nfc_check_empty_chunk (struct nand_chip*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  marvell_nfc_disable_hw_ecc (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_enable_hw_ecc (struct nand_chip*) ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_read_chunk (struct nand_chip*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int marvell_nfc_hw_ecc_correct (struct nand_chip*,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_change_read_column_op (struct nand_chip*,int,int /*<<< orphan*/ *,int,int) ; 
 TYPE_1__* to_marvell_nand (struct nand_chip*) ; 

__attribute__((used)) static int marvell_nfc_hw_ecc_bch_read_page(struct mtd_info *mtd,
					    struct nand_chip *chip,
					    u8 *buf, int oob_required,
					    int page)
{
	const struct marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	int data_len = lt->data_bytes, spare_len = lt->spare_bytes, ecc_len;
	u8 *data = buf, *spare = chip->oob_poi, *ecc;
	int max_bitflips = 0;
	u32 failure_mask = 0;
	int chunk, ecc_offset_in_page, ret;

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
	 *
	 * However, for any subpage read error reported by ->correct(), the ECC
	 * bytes must be read in raw mode and the full subpage must be checked
	 * to see if it is entirely empty of if there was an actual error.
	 */
	for (chunk = 0; chunk < lt->nchunks; chunk++) {
		/* No failure reported for this chunk, move to the next one */
		if (!(failure_mask & BIT(chunk)))
			continue;

		/* Derive ECC bytes positions (in page/buffer) and length */
		ecc = chip->oob_poi +
			(lt->full_chunk_cnt * lt->spare_bytes) +
			lt->last_spare_bytes +
			(chunk * ALIGN(lt->ecc_bytes, 32));
		ecc_offset_in_page =
			(chunk * (lt->data_bytes + lt->spare_bytes +
				  lt->ecc_bytes)) +
			(chunk < lt->full_chunk_cnt ?
			 lt->data_bytes + lt->spare_bytes :
			 lt->last_data_bytes + lt->last_spare_bytes);
		ecc_len = chunk < lt->full_chunk_cnt ?
			lt->ecc_bytes : lt->last_ecc_bytes;

		/* Do the actual raw read of the ECC bytes */
		nand_change_read_column_op(chip, ecc_offset_in_page,
					   ecc, ecc_len, false);

		/* Derive data/spare bytes positions (in buffer) and length */
		data = buf + (chunk * lt->data_bytes);
		data_len = chunk < lt->full_chunk_cnt ?
			lt->data_bytes : lt->last_data_bytes;
		spare = chip->oob_poi + (chunk * (lt->spare_bytes +
						  lt->ecc_bytes));
		spare_len = chunk < lt->full_chunk_cnt ?
			lt->spare_bytes : lt->last_spare_bytes;

		/* Check the entire chunk (data + spare + ecc) for emptyness */
		marvell_nfc_check_empty_chunk(chip, data, data_len, spare,
					      spare_len, ecc, ecc_len,
					      &max_bitflips);
	}

	return max_bitflips;
}