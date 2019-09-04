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
struct nand_chip {int dummy; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;
struct denali_nand_info {int caps; } ;

/* Variables and functions */
 int DENALI_CAP_HW_ECC_FIXUP ; 
 int EBADMSG ; 
 int denali_check_erased_page (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ *,unsigned long,int) ; 
 int denali_data_xfer (struct denali_nand_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int denali_hw_ecc_fixup (struct mtd_info*,struct denali_nand_info*,unsigned long*) ; 
 int denali_read_oob (struct mtd_info*,struct nand_chip*,int) ; 
 int denali_sw_ecc_fixup (struct mtd_info*,struct denali_nand_info*,unsigned long*,int /*<<< orphan*/ *) ; 
 struct denali_nand_info* mtd_to_denali (struct mtd_info*) ; 

__attribute__((used)) static int denali_read_page(struct mtd_info *mtd, struct nand_chip *chip,
			    uint8_t *buf, int oob_required, int page)
{
	struct denali_nand_info *denali = mtd_to_denali(mtd);
	unsigned long uncor_ecc_flags = 0;
	int stat = 0;
	int ret;

	ret = denali_data_xfer(denali, buf, mtd->writesize, page, 0, 0);
	if (ret && ret != -EBADMSG)
		return ret;

	if (denali->caps & DENALI_CAP_HW_ECC_FIXUP)
		stat = denali_hw_ecc_fixup(mtd, denali, &uncor_ecc_flags);
	else if (ret == -EBADMSG)
		stat = denali_sw_ecc_fixup(mtd, denali, &uncor_ecc_flags, buf);

	if (stat < 0)
		return stat;

	if (uncor_ecc_flags) {
		ret = denali_read_oob(mtd, chip, page);
		if (ret)
			return ret;

		stat = denali_check_erased_page(mtd, chip, buf,
						uncor_ecc_flags, stat);
	}

	return stat;
}