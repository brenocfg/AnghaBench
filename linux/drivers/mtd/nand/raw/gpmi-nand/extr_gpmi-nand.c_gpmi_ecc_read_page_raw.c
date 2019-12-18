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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;
struct mtd_info {size_t writesize; size_t oobsize; } ;
struct bch_geometry {int ecc_chunk_size; int ecc_strength; int gf_len; size_t metadata_size; int ecc_chunk_count; } ;
struct gpmi_nand_data {scalar_t__ swap_block_mark; int /*<<< orphan*/ * raw_buffer; struct bch_geometry bch_geometry; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpmi_copy_bits (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 struct gpmi_nand_data* nand_get_controller_data (struct nand_chip*) ; 
 int nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpmi_ecc_read_page_raw(struct nand_chip *chip, uint8_t *buf,
				  int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct gpmi_nand_data *this = nand_get_controller_data(chip);
	struct bch_geometry *nfc_geo = &this->bch_geometry;
	int eccsize = nfc_geo->ecc_chunk_size;
	int eccbits = nfc_geo->ecc_strength * nfc_geo->gf_len;
	u8 *tmp_buf = this->raw_buffer;
	size_t src_bit_off;
	size_t oob_bit_off;
	size_t oob_byte_off;
	uint8_t *oob = chip->oob_poi;
	int step;
	int ret;

	ret = nand_read_page_op(chip, page, 0, tmp_buf,
				mtd->writesize + mtd->oobsize);
	if (ret)
		return ret;

	/*
	 * If required, swap the bad block marker and the data stored in the
	 * metadata section, so that we don't wrongly consider a block as bad.
	 *
	 * See the layout description for a detailed explanation on why this
	 * is needed.
	 */
	if (this->swap_block_mark)
		swap(tmp_buf[0], tmp_buf[mtd->writesize]);

	/*
	 * Copy the metadata section into the oob buffer (this section is
	 * guaranteed to be aligned on a byte boundary).
	 */
	if (oob_required)
		memcpy(oob, tmp_buf, nfc_geo->metadata_size);

	oob_bit_off = nfc_geo->metadata_size * 8;
	src_bit_off = oob_bit_off;

	/* Extract interleaved payload data and ECC bits */
	for (step = 0; step < nfc_geo->ecc_chunk_count; step++) {
		if (buf)
			gpmi_copy_bits(buf, step * eccsize * 8,
				       tmp_buf, src_bit_off,
				       eccsize * 8);
		src_bit_off += eccsize * 8;

		/* Align last ECC block to align a byte boundary */
		if (step == nfc_geo->ecc_chunk_count - 1 &&
		    (oob_bit_off + eccbits) % 8)
			eccbits += 8 - ((oob_bit_off + eccbits) % 8);

		if (oob_required)
			gpmi_copy_bits(oob, oob_bit_off,
				       tmp_buf, src_bit_off,
				       eccbits);

		src_bit_off += eccbits;
		oob_bit_off += eccbits;
	}

	if (oob_required) {
		oob_byte_off = oob_bit_off / 8;

		if (oob_byte_off < mtd->oobsize)
			memcpy(oob + oob_byte_off,
			       tmp_buf + mtd->writesize + oob_byte_off,
			       mtd->oobsize - oob_byte_off);
	}

	return 0;
}