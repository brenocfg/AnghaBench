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
typedef  scalar_t__ u_char ;
typedef  int u32 ;
struct nand_ecc_ctrl {int steps; int bytes; int size; } ;
struct TYPE_3__ {struct nand_ecc_ctrl ecc; } ;
struct omap_nand_info {int ecc_opt; TYPE_2__* pdev; int /*<<< orphan*/  elm_dev; TYPE_1__ nand; } ;
struct mtd_info {int dummy; } ;
struct elm_errorvec {int error_reported; int error_count; int* error_loc; scalar_t__ error_uncorrectable; } ;
typedef  int /*<<< orphan*/  err_vec ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BCH4_BIT_PAD ; 
 int EBADMSG ; 
 int EINVAL ; 
 int ERROR_VECTOR_MAX ; 
#define  OMAP_ECC_BCH16_CODE_HW 130 
#define  OMAP_ECC_BCH4_CODE_HW 129 
#define  OMAP_ECC_BCH8_CODE_HW 128 
 scalar_t__* bch16_vector ; 
 scalar_t__* bch4_vector ; 
 scalar_t__* bch8_vector ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  elm_decode_bch_error_page (int /*<<< orphan*/ ,scalar_t__*,struct elm_errorvec*) ; 
 int erased_sector_bitflips (scalar_t__*,scalar_t__*,struct omap_nand_info*) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (struct elm_errorvec*,int /*<<< orphan*/ ,int) ; 
 struct omap_nand_info* mtd_to_omap (struct mtd_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,scalar_t__) ; 

__attribute__((used)) static int omap_elm_correct_data(struct mtd_info *mtd, u_char *data,
				u_char *read_ecc, u_char *calc_ecc)
{
	struct omap_nand_info *info = mtd_to_omap(mtd);
	struct nand_ecc_ctrl *ecc = &info->nand.ecc;
	int eccsteps = info->nand.ecc.steps;
	int i , j, stat = 0;
	int eccflag, actual_eccbytes;
	struct elm_errorvec err_vec[ERROR_VECTOR_MAX];
	u_char *ecc_vec = calc_ecc;
	u_char *spare_ecc = read_ecc;
	u_char *erased_ecc_vec;
	u_char *buf;
	int bitflip_count;
	bool is_error_reported = false;
	u32 bit_pos, byte_pos, error_max, pos;
	int err;

	switch (info->ecc_opt) {
	case OMAP_ECC_BCH4_CODE_HW:
		/* omit  7th ECC byte reserved for ROM code compatibility */
		actual_eccbytes = ecc->bytes - 1;
		erased_ecc_vec = bch4_vector;
		break;
	case OMAP_ECC_BCH8_CODE_HW:
		/* omit 14th ECC byte reserved for ROM code compatibility */
		actual_eccbytes = ecc->bytes - 1;
		erased_ecc_vec = bch8_vector;
		break;
	case OMAP_ECC_BCH16_CODE_HW:
		actual_eccbytes = ecc->bytes;
		erased_ecc_vec = bch16_vector;
		break;
	default:
		dev_err(&info->pdev->dev, "invalid driver configuration\n");
		return -EINVAL;
	}

	/* Initialize elm error vector to zero */
	memset(err_vec, 0, sizeof(err_vec));

	for (i = 0; i < eccsteps ; i++) {
		eccflag = 0;	/* initialize eccflag */

		/*
		 * Check any error reported,
		 * In case of error, non zero ecc reported.
		 */
		for (j = 0; j < actual_eccbytes; j++) {
			if (calc_ecc[j] != 0) {
				eccflag = 1; /* non zero ecc, error present */
				break;
			}
		}

		if (eccflag == 1) {
			if (memcmp(calc_ecc, erased_ecc_vec,
						actual_eccbytes) == 0) {
				/*
				 * calc_ecc[] matches pattern for ECC(all 0xff)
				 * so this is definitely an erased-page
				 */
			} else {
				buf = &data[info->nand.ecc.size * i];
				/*
				 * count number of 0-bits in read_buf.
				 * This check can be removed once a similar
				 * check is introduced in generic NAND driver
				 */
				bitflip_count = erased_sector_bitflips(
						buf, read_ecc, info);
				if (bitflip_count) {
					/*
					 * number of 0-bits within ECC limits
					 * So this may be an erased-page
					 */
					stat += bitflip_count;
				} else {
					/*
					 * Too many 0-bits. It may be a
					 * - programmed-page, OR
					 * - erased-page with many bit-flips
					 * So this page requires check by ELM
					 */
					err_vec[i].error_reported = true;
					is_error_reported = true;
				}
			}
		}

		/* Update the ecc vector */
		calc_ecc += ecc->bytes;
		read_ecc += ecc->bytes;
	}

	/* Check if any error reported */
	if (!is_error_reported)
		return stat;

	/* Decode BCH error using ELM module */
	elm_decode_bch_error_page(info->elm_dev, ecc_vec, err_vec);

	err = 0;
	for (i = 0; i < eccsteps; i++) {
		if (err_vec[i].error_uncorrectable) {
			dev_err(&info->pdev->dev,
				"uncorrectable bit-flips found\n");
			err = -EBADMSG;
		} else if (err_vec[i].error_reported) {
			for (j = 0; j < err_vec[i].error_count; j++) {
				switch (info->ecc_opt) {
				case OMAP_ECC_BCH4_CODE_HW:
					/* Add 4 bits to take care of padding */
					pos = err_vec[i].error_loc[j] +
						BCH4_BIT_PAD;
					break;
				case OMAP_ECC_BCH8_CODE_HW:
				case OMAP_ECC_BCH16_CODE_HW:
					pos = err_vec[i].error_loc[j];
					break;
				default:
					return -EINVAL;
				}
				error_max = (ecc->size + actual_eccbytes) * 8;
				/* Calculate bit position of error */
				bit_pos = pos % 8;

				/* Calculate byte position of error */
				byte_pos = (error_max - pos - 1) / 8;

				if (pos < error_max) {
					if (byte_pos < 512) {
						pr_debug("bitflip@dat[%d]=%x\n",
						     byte_pos, data[byte_pos]);
						data[byte_pos] ^= 1 << bit_pos;
					} else {
						pr_debug("bitflip@oob[%d]=%x\n",
							(byte_pos - 512),
						     spare_ecc[byte_pos - 512]);
						spare_ecc[byte_pos - 512] ^=
							1 << bit_pos;
					}
				} else {
					dev_err(&info->pdev->dev,
						"invalid bit-flip @ %d:%d\n",
						byte_pos, bit_pos);
					err = -EBADMSG;
				}
			}
		}

		/* Update number of correctable errors */
		stat += err_vec[i].error_count;

		/* Update page data with sector size */
		data += ecc->size;
		spare_ecc += ecc->bytes;
	}

	return (err) ? err : stat;
}