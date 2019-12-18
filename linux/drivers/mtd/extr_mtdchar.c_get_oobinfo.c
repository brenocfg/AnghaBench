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
typedef  scalar_t__ u32 ;
struct nand_oobinfo {scalar_t__** oobfree; int /*<<< orphan*/  useecc; scalar_t__ eccbytes; scalar_t__* eccpos; } ;
struct mtd_oob_region {int length; scalar_t__ offset; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  MTD_NANDECC_AUTOPLACE ; 
 int /*<<< orphan*/  memset (struct nand_oobinfo*,int /*<<< orphan*/ ,int) ; 
 int mtd_ooblayout_ecc (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_region*) ; 
 int mtd_ooblayout_free (struct mtd_info*,int,struct mtd_oob_region*) ; 

__attribute__((used)) static int get_oobinfo(struct mtd_info *mtd, struct nand_oobinfo *to)
{
	struct mtd_oob_region oobregion;
	int i, section = 0, ret;

	if (!mtd || !to)
		return -EINVAL;

	memset(to, 0, sizeof(*to));

	to->eccbytes = 0;
	for (i = 0; i < ARRAY_SIZE(to->eccpos);) {
		u32 eccpos;

		ret = mtd_ooblayout_ecc(mtd, section++, &oobregion);
		if (ret < 0) {
			if (ret != -ERANGE)
				return ret;

			break;
		}

		if (oobregion.length + i > ARRAY_SIZE(to->eccpos))
			return -EINVAL;

		eccpos = oobregion.offset;
		for (; eccpos < oobregion.offset + oobregion.length; i++) {
			to->eccpos[i] = eccpos++;
			to->eccbytes++;
		}
	}

	for (i = 0; i < 8; i++) {
		ret = mtd_ooblayout_free(mtd, i, &oobregion);
		if (ret < 0) {
			if (ret != -ERANGE)
				return ret;

			break;
		}

		to->oobfree[i][0] = oobregion.offset;
		to->oobfree[i][1] = oobregion.length;
	}

	to->useecc = MTD_NANDECC_AUTOPLACE;

	return 0;
}