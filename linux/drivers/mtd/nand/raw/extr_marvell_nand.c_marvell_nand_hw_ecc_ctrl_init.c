#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nand_ecc_ctrl {scalar_t__ size; int strength; int /*<<< orphan*/  write_oob; int /*<<< orphan*/  write_oob_raw; int /*<<< orphan*/  write_page; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  read_oob; int /*<<< orphan*/  read_oob_raw; int /*<<< orphan*/  read_page; int /*<<< orphan*/  read_page_raw; int /*<<< orphan*/  steps; } ;
struct TYPE_5__ {int /*<<< orphan*/  algo; } ;
struct nand_chip {TYPE_2__ ecc; int /*<<< orphan*/  bbt_options; int /*<<< orphan*/  controller; } ;
struct mtd_info {scalar_t__ writesize; int oobsize; } ;
struct marvell_nfc {int /*<<< orphan*/  dev; TYPE_1__* caps; } ;
struct marvell_hw_ecc_layout {int writesize; scalar_t__ chunk; int strength; scalar_t__ data_bytes; int /*<<< orphan*/  nchunks; } ;
struct TYPE_6__ {struct marvell_hw_ecc_layout const* layout; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_nfcv2; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct marvell_hw_ecc_layout*) ; 
 int ENOTSUPP ; 
 scalar_t__ MAX_CHUNK_SIZE ; 
 int /*<<< orphan*/  NAND_BBT_NO_OOB_BBM ; 
 int /*<<< orphan*/  NAND_ECC_BCH ; 
 int /*<<< orphan*/  NAND_ECC_HAMMING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  marvell_nand_ooblayout_ops ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_read_oob ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_read_oob_raw ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_read_page ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_read_page_raw ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_write_oob ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_write_oob_raw ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_write_page ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_bch_write_page_raw ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_hmg_read_oob_raw ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_hmg_read_page ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_hmg_read_page_raw ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_hmg_write_oob_raw ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_hmg_write_page ; 
 int /*<<< orphan*/  marvell_nfc_hw_ecc_hmg_write_page_raw ; 
 struct marvell_hw_ecc_layout* marvell_nfc_layouts ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 TYPE_3__* to_marvell_nand (struct nand_chip*) ; 
 struct marvell_nfc* to_marvell_nfc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_nand_hw_ecc_ctrl_init(struct mtd_info *mtd,
					 struct nand_ecc_ctrl *ecc)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct marvell_nfc *nfc = to_marvell_nfc(chip->controller);
	const struct marvell_hw_ecc_layout *l;
	int i;

	if (!nfc->caps->is_nfcv2 &&
	    (mtd->writesize + mtd->oobsize > MAX_CHUNK_SIZE)) {
		dev_err(nfc->dev,
			"NFCv1: writesize (%d) cannot be bigger than a chunk (%d)\n",
			mtd->writesize, MAX_CHUNK_SIZE - mtd->oobsize);
		return -ENOTSUPP;
	}

	to_marvell_nand(chip)->layout = NULL;
	for (i = 0; i < ARRAY_SIZE(marvell_nfc_layouts); i++) {
		l = &marvell_nfc_layouts[i];
		if (mtd->writesize == l->writesize &&
		    ecc->size == l->chunk && ecc->strength == l->strength) {
			to_marvell_nand(chip)->layout = l;
			break;
		}
	}

	if (!to_marvell_nand(chip)->layout ||
	    (!nfc->caps->is_nfcv2 && ecc->strength > 1)) {
		dev_err(nfc->dev,
			"ECC strength %d at page size %d is not supported\n",
			ecc->strength, mtd->writesize);
		return -ENOTSUPP;
	}

	/* Special care for the layout 2k/8-bit/512B  */
	if (l->writesize == 2048 && l->strength == 8) {
		if (mtd->oobsize < 128) {
			dev_err(nfc->dev, "Requested layout needs at least 128 OOB bytes\n");
			return -ENOTSUPP;
		} else {
			chip->bbt_options |= NAND_BBT_NO_OOB_BBM;
		}
	}

	mtd_set_ooblayout(mtd, &marvell_nand_ooblayout_ops);
	ecc->steps = l->nchunks;
	ecc->size = l->data_bytes;

	if (ecc->strength == 1) {
		chip->ecc.algo = NAND_ECC_HAMMING;
		ecc->read_page_raw = marvell_nfc_hw_ecc_hmg_read_page_raw;
		ecc->read_page = marvell_nfc_hw_ecc_hmg_read_page;
		ecc->read_oob_raw = marvell_nfc_hw_ecc_hmg_read_oob_raw;
		ecc->read_oob = ecc->read_oob_raw;
		ecc->write_page_raw = marvell_nfc_hw_ecc_hmg_write_page_raw;
		ecc->write_page = marvell_nfc_hw_ecc_hmg_write_page;
		ecc->write_oob_raw = marvell_nfc_hw_ecc_hmg_write_oob_raw;
		ecc->write_oob = ecc->write_oob_raw;
	} else {
		chip->ecc.algo = NAND_ECC_BCH;
		ecc->strength = 16;
		ecc->read_page_raw = marvell_nfc_hw_ecc_bch_read_page_raw;
		ecc->read_page = marvell_nfc_hw_ecc_bch_read_page;
		ecc->read_oob_raw = marvell_nfc_hw_ecc_bch_read_oob_raw;
		ecc->read_oob = marvell_nfc_hw_ecc_bch_read_oob;
		ecc->write_page_raw = marvell_nfc_hw_ecc_bch_write_page_raw;
		ecc->write_page = marvell_nfc_hw_ecc_bch_write_page;
		ecc->write_oob_raw = marvell_nfc_hw_ecc_bch_write_oob_raw;
		ecc->write_oob = marvell_nfc_hw_ecc_bch_write_oob;
	}

	return 0;
}