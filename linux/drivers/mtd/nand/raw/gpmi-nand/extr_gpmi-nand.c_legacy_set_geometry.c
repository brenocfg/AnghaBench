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
struct mtd_info {int oobsize; int writesize; } ;
struct bch_geometry {int metadata_size; int gf_len; int ecc_chunk_size; int ecc_chunk_count; int ecc_strength; int page_size; int payload_size; unsigned int auxiliary_size; unsigned int auxiliary_status_offset; unsigned int block_mark_byte_offset; unsigned int block_mark_bit_offset; } ;
struct gpmi_nand_data {int /*<<< orphan*/  swap_block_mark; TYPE_1__* devdata; int /*<<< orphan*/  dev; int /*<<< orphan*/  nand; struct bch_geometry bch_geometry; } ;
struct TYPE_2__ {int /*<<< orphan*/  bch_max_ecc_strength; } ;

/* Variables and functions */
 unsigned int ALIGN (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int get_ecc_strength (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  gpmi_check_ecc (struct gpmi_nand_data*) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int legacy_set_geometry(struct gpmi_nand_data *this)
{
	struct bch_geometry *geo = &this->bch_geometry;
	struct mtd_info *mtd = nand_to_mtd(&this->nand);
	unsigned int metadata_size;
	unsigned int status_size;
	unsigned int block_mark_bit_offset;

	/*
	 * The size of the metadata can be changed, though we set it to 10
	 * bytes now. But it can't be too large, because we have to save
	 * enough space for BCH.
	 */
	geo->metadata_size = 10;

	/* The default for the length of Galois Field. */
	geo->gf_len = 13;

	/* The default for chunk size. */
	geo->ecc_chunk_size = 512;
	while (geo->ecc_chunk_size < mtd->oobsize) {
		geo->ecc_chunk_size *= 2; /* keep C >= O */
		geo->gf_len = 14;
	}

	geo->ecc_chunk_count = mtd->writesize / geo->ecc_chunk_size;

	/* We use the same ECC strength for all chunks. */
	geo->ecc_strength = get_ecc_strength(this);
	if (!gpmi_check_ecc(this)) {
		dev_err(this->dev,
			"ecc strength: %d cannot be supported by the controller (%d)\n"
			"try to use minimum ecc strength that NAND chip required\n",
			geo->ecc_strength,
			this->devdata->bch_max_ecc_strength);
		return -EINVAL;
	}

	geo->page_size = mtd->writesize + geo->metadata_size +
		(geo->gf_len * geo->ecc_strength * geo->ecc_chunk_count) / 8;
	geo->payload_size = mtd->writesize;

	/*
	 * The auxiliary buffer contains the metadata and the ECC status. The
	 * metadata is padded to the nearest 32-bit boundary. The ECC status
	 * contains one byte for every ECC chunk, and is also padded to the
	 * nearest 32-bit boundary.
	 */
	metadata_size = ALIGN(geo->metadata_size, 4);
	status_size   = ALIGN(geo->ecc_chunk_count, 4);

	geo->auxiliary_size = metadata_size + status_size;
	geo->auxiliary_status_offset = metadata_size;

	if (!this->swap_block_mark)
		return 0;

	/*
	 * We need to compute the byte and bit offsets of
	 * the physical block mark within the ECC-based view of the page.
	 *
	 * NAND chip with 2K page shows below:
	 *                                             (Block Mark)
	 *                                                   |      |
	 *                                                   |  D   |
	 *                                                   |<---->|
	 *                                                   V      V
	 *    +---+----------+-+----------+-+----------+-+----------+-+
	 *    | M |   data   |E|   data   |E|   data   |E|   data   |E|
	 *    +---+----------+-+----------+-+----------+-+----------+-+
	 *
	 * The position of block mark moves forward in the ECC-based view
	 * of page, and the delta is:
	 *
	 *                   E * G * (N - 1)
	 *             D = (---------------- + M)
	 *                          8
	 *
	 * With the formula to compute the ECC strength, and the condition
	 *       : C >= O         (C is the ecc chunk size)
	 *
	 * It's easy to deduce to the following result:
	 *
	 *         E * G       (O - M)      C - M         C - M
	 *      ----------- <= ------- <=  --------  <  ---------
	 *           8            N           N          (N - 1)
	 *
	 *  So, we get:
	 *
	 *                   E * G * (N - 1)
	 *             D = (---------------- + M) < C
	 *                          8
	 *
	 *  The above inequality means the position of block mark
	 *  within the ECC-based view of the page is still in the data chunk,
	 *  and it's NOT in the ECC bits of the chunk.
	 *
	 *  Use the following to compute the bit position of the
	 *  physical block mark within the ECC-based view of the page:
	 *          (page_size - D) * 8
	 *
	 *  --Huang Shijie
	 */
	block_mark_bit_offset = mtd->writesize * 8 -
		(geo->ecc_strength * geo->gf_len * (geo->ecc_chunk_count - 1)
				+ geo->metadata_size * 8);

	geo->block_mark_byte_offset = block_mark_bit_offset / 8;
	geo->block_mark_bit_offset  = block_mark_bit_offset % 8;
	return 0;
}