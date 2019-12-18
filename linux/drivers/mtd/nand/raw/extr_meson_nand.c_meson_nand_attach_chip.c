#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  read_oob; int /*<<< orphan*/  read_oob_raw; int /*<<< orphan*/  read_page; int /*<<< orphan*/  read_page_raw; void* write_oob; void* write_oob_raw; int /*<<< orphan*/  write_page; int /*<<< orphan*/  write_page_raw; int /*<<< orphan*/  mode; } ;
struct nand_chip {int bbt_options; int options; TYPE_2__ ecc; } ;
struct mtd_info {int writesize; scalar_t__ oobsize; scalar_t__ name; } ;
struct meson_nfc_nand_chip {int /*<<< orphan*/ * sels; } ;
struct meson_nfc {int /*<<< orphan*/  dev; TYPE_1__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  ecc_caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_USE_FLASH ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int NAND_NO_SUBPAGE_WRITE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 scalar_t__ devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int meson_chip_buffer_init (struct nand_chip*) ; 
 int meson_nand_bch_mode (struct nand_chip*) ; 
 int /*<<< orphan*/  meson_nfc_read_oob ; 
 int /*<<< orphan*/  meson_nfc_read_oob_raw ; 
 int /*<<< orphan*/  meson_nfc_read_page_hwecc ; 
 int /*<<< orphan*/  meson_nfc_read_page_raw ; 
 int /*<<< orphan*/  meson_nfc_write_page_hwecc ; 
 int /*<<< orphan*/  meson_nfc_write_page_raw ; 
 int /*<<< orphan*/  meson_ooblayout_ops ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 int nand_ecc_choose_conf (struct nand_chip*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct meson_nfc* nand_get_controller_data (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 void* nand_write_oob_std ; 
 struct meson_nfc_nand_chip* to_meson_nand (struct nand_chip*) ; 

__attribute__((used)) static int meson_nand_attach_chip(struct nand_chip *nand)
{
	struct meson_nfc *nfc = nand_get_controller_data(nand);
	struct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);
	struct mtd_info *mtd = nand_to_mtd(nand);
	int nsectors = mtd->writesize / 1024;
	int ret;

	if (!mtd->name) {
		mtd->name = devm_kasprintf(nfc->dev, GFP_KERNEL,
					   "%s:nand%d",
					   dev_name(nfc->dev),
					   meson_chip->sels[0]);
		if (!mtd->name)
			return -ENOMEM;
	}

	if (nand->bbt_options & NAND_BBT_USE_FLASH)
		nand->bbt_options |= NAND_BBT_NO_OOB;

	nand->options |= NAND_NO_SUBPAGE_WRITE;

	ret = nand_ecc_choose_conf(nand, nfc->data->ecc_caps,
				   mtd->oobsize - 2 * nsectors);
	if (ret) {
		dev_err(nfc->dev, "failed to ECC init\n");
		return -EINVAL;
	}

	mtd_set_ooblayout(mtd, &meson_ooblayout_ops);

	ret = meson_nand_bch_mode(nand);
	if (ret)
		return -EINVAL;

	nand->ecc.mode = NAND_ECC_HW;
	nand->ecc.write_page_raw = meson_nfc_write_page_raw;
	nand->ecc.write_page = meson_nfc_write_page_hwecc;
	nand->ecc.write_oob_raw = nand_write_oob_std;
	nand->ecc.write_oob = nand_write_oob_std;

	nand->ecc.read_page_raw = meson_nfc_read_page_raw;
	nand->ecc.read_page = meson_nfc_read_page_hwecc;
	nand->ecc.read_oob_raw = meson_nfc_read_oob_raw;
	nand->ecc.read_oob = meson_nfc_read_oob;

	if (nand->options & NAND_BUSWIDTH_16) {
		dev_err(nfc->dev, "16bits bus width not supported");
		return -EINVAL;
	}
	ret = meson_chip_buffer_init(nand);
	if (ret)
		return -ENOMEM;

	return ret;
}