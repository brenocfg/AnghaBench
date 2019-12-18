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
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;
struct bch_geometry {int /*<<< orphan*/  auxiliary_status_offset; int /*<<< orphan*/  ecc_chunk_count; int /*<<< orphan*/  page_size; } ;
struct gpmi_nand_data {int bch; scalar_t__ auxiliary_virt; struct bch_geometry bch_geometry; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_mark_swapping (struct gpmi_nand_data*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gpmi_bch_layout_std (struct gpmi_nand_data*) ; 
 unsigned int gpmi_count_bitflips (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 int nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int gpmi_ecc_read_page(struct nand_chip *chip, uint8_t *buf,
			      int oob_required, int page)
{
	struct gpmi_nand_data *this = nand_get_controller_data(chip);
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct bch_geometry *geo = &this->bch_geometry;
	unsigned int max_bitflips;
	int ret;

	gpmi_bch_layout_std(this);
	this->bch = true;

	ret = nand_read_page_op(chip, page, 0, buf, geo->page_size);
	if (ret)
		return ret;

	max_bitflips = gpmi_count_bitflips(chip, buf, 0,
					   geo->ecc_chunk_count,
					   geo->auxiliary_status_offset);

	/* handle the block mark swapping */
	block_mark_swapping(this, buf, this->auxiliary_virt);

	if (oob_required) {
		/*
		 * It's time to deliver the OOB bytes. See gpmi_ecc_read_oob()
		 * for details about our policy for delivering the OOB.
		 *
		 * We fill the caller's buffer with set bits, and then copy the
		 * block mark to th caller's buffer. Note that, if block mark
		 * swapping was necessary, it has already been done, so we can
		 * rely on the first byte of the auxiliary buffer to contain
		 * the block mark.
		 */
		memset(chip->oob_poi, ~0, mtd->oobsize);
		chip->oob_poi[0] = ((uint8_t *)this->auxiliary_virt)[0];
	}

	return max_bitflips;
}