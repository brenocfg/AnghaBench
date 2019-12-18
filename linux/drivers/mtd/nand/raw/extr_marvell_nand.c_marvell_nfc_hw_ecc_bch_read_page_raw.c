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
struct mtd_info {int /*<<< orphan*/  oobsize; } ;
struct marvell_hw_ecc_layout {int data_bytes; int spare_bytes; int ecc_bytes; int full_chunk_cnt; int last_spare_bytes; int nchunks; int last_data_bytes; int last_ecc_bytes; } ;
struct TYPE_2__ {struct marvell_hw_ecc_layout* layout; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  marvell_nfc_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_change_read_column_op (struct nand_chip*,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nand_read_data_op (struct nand_chip*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 TYPE_1__* to_marvell_nand (struct nand_chip*) ; 

__attribute__((used)) static int marvell_nfc_hw_ecc_bch_read_page_raw(struct nand_chip *chip, u8 *buf,
						int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const struct marvell_hw_ecc_layout *lt = to_marvell_nand(chip)->layout;
	u8 *oob = chip->oob_poi;
	int chunk_size = lt->data_bytes + lt->spare_bytes + lt->ecc_bytes;
	int ecc_offset = (lt->full_chunk_cnt * lt->spare_bytes) +
		lt->last_spare_bytes;
	int data_len = lt->data_bytes;
	int spare_len = lt->spare_bytes;
	int ecc_len = lt->ecc_bytes;
	int chunk;

	marvell_nfc_select_target(chip, chip->cur_cs);

	if (oob_required)
		memset(chip->oob_poi, 0xFF, mtd->oobsize);

	nand_read_page_op(chip, page, 0, NULL, 0);

	for (chunk = 0; chunk < lt->nchunks; chunk++) {
		/* Update last chunk length */
		if (chunk >= lt->full_chunk_cnt) {
			data_len = lt->last_data_bytes;
			spare_len = lt->last_spare_bytes;
			ecc_len = lt->last_ecc_bytes;
		}

		/* Read data bytes*/
		nand_change_read_column_op(chip, chunk * chunk_size,
					   buf + (lt->data_bytes * chunk),
					   data_len, false);

		/* Read spare bytes */
		nand_read_data_op(chip, oob + (lt->spare_bytes * chunk),
				  spare_len, false);

		/* Read ECC bytes */
		nand_read_data_op(chip, oob + ecc_offset +
				  (ALIGN(lt->ecc_bytes, 32) * chunk),
				  ecc_len, false);
	}

	return 0;
}