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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int steps; int size; int bytes; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; TYPE_1__ ecc; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct denali_nand_info {int oob_skip_bytes; void* buf; } ;

/* Variables and functions */
 int denali_data_xfer (struct denali_nand_info*,void*,size_t,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 

__attribute__((used)) static int denali_read_page_raw(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int oob_required, int page)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	int writesize = mtd->writesize;
	int oobsize = mtd->oobsize;
	int ecc_steps = chip->ecc.steps;
	int ecc_size = chip->ecc.size;
	int ecc_bytes = chip->ecc.bytes;
	void *tmp_buf = denali->buf;
	int oob_skip = denali->oob_skip_bytes;
	size_t size = writesize + oobsize;
	int ret, i, pos, len;

	ret = denali_data_xfer(denali, tmp_buf, size, page, 1, 0);
	if (ret)
		return ret;

	/* Arrange the buffer for syndrome payload/ecc layout */
	if (buf) {
		for (i = 0; i < ecc_steps; i++) {
			pos = i * (ecc_size + ecc_bytes);
			len = ecc_size;

			if (pos >= writesize)
				pos += oob_skip;
			else if (pos + len > writesize)
				len = writesize - pos;

			memcpy(buf, tmp_buf + pos, len);
			buf += len;
			if (len < ecc_size) {
				len = ecc_size - len;
				memcpy(buf, tmp_buf + writesize + oob_skip,
				       len);
				buf += len;
			}
		}
	}

	if (oob_required) {
		uint8_t *oob = chip->oob_poi;

		/* BBM at the beginning of the OOB area */
		memcpy(oob, tmp_buf + writesize, oob_skip);
		oob += oob_skip;

		/* OOB ECC */
		for (i = 0; i < ecc_steps; i++) {
			pos = ecc_size + i * (ecc_size + ecc_bytes);
			len = ecc_bytes;

			if (pos >= writesize)
				pos += oob_skip;
			else if (pos + len > writesize)
				len = writesize - pos;

			memcpy(oob, tmp_buf + pos, len);
			oob += len;
			if (len < ecc_bytes) {
				len = ecc_bytes - len;
				memcpy(oob, tmp_buf + writesize + oob_skip,
				       len);
				oob += len;
			}
		}

		/* OOB free */
		len = oobsize - (oob - chip->oob_poi);
		memcpy(oob, tmp_buf + size - len, len);
	}

	return 0;
}