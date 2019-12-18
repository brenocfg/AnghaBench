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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int /*<<< orphan*/  const* oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;
struct bch_geometry {int /*<<< orphan*/  page_size; int /*<<< orphan*/  auxiliary_size; } ;
struct gpmi_nand_data {int bch; int /*<<< orphan*/ * auxiliary_virt; int /*<<< orphan*/ * data_buffer_dma; scalar_t__ swap_block_mark; int /*<<< orphan*/  dev; struct bch_geometry bch_geometry; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_mark_swapping (struct gpmi_nand_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpmi_bch_layout_std (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 int nand_prog_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int gpmi_ecc_write_page(struct nand_chip *chip, const uint8_t *buf,
			       int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct gpmi_nand_data *this = nand_get_controller_data(chip);
	struct bch_geometry *nfc_geo = &this->bch_geometry;
	int ret;

	dev_dbg(this->dev, "ecc write page.\n");

	gpmi_bch_layout_std(this);
	this->bch = true;

	memcpy(this->auxiliary_virt, chip->oob_poi, nfc_geo->auxiliary_size);

	if (this->swap_block_mark) {
		/*
		 * When doing bad block marker swapping we must always copy the
		 * input buffer as we can't modify the const buffer.
		 */
		memcpy(this->data_buffer_dma, buf, mtd->writesize);
		buf = this->data_buffer_dma;
		block_mark_swapping(this, this->data_buffer_dma,
				    this->auxiliary_virt);
	}

	ret = nand_prog_page_op(chip, page, 0, buf, nfc_geo->page_size);

	return ret;
}