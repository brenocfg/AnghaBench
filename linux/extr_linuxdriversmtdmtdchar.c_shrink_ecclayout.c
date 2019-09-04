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
typedef  scalar_t__ u32 ;
struct nand_ecclayout_user {TYPE_1__* oobfree; int /*<<< orphan*/  oobavail; scalar_t__ eccbytes; scalar_t__* eccpos; } ;
struct mtd_oob_region {scalar_t__ offset; scalar_t__ length; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ length; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int MTD_MAX_ECCPOS_ENTRIES ; 
 int MTD_MAX_OOBFREE_ENTRIES ; 
 int /*<<< orphan*/  memset (struct nand_ecclayout_user*,int /*<<< orphan*/ ,int) ; 
 int mtd_ooblayout_ecc (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_region*) ; 
 int mtd_ooblayout_free (struct mtd_info*,int,struct mtd_oob_region*) ; 

__attribute__((used)) static int shrink_ecclayout(struct mtd_info *mtd,
			    struct nand_ecclayout_user *to)
{
	struct mtd_oob_region oobregion;
	int i, section = 0, ret;

	if (!mtd || !to)
		return -EINVAL;

	memset(to, 0, sizeof(*to));

	to->eccbytes = 0;
	for (i = 0; i < MTD_MAX_ECCPOS_ENTRIES;) {
		u32 eccpos;

		ret = mtd_ooblayout_ecc(mtd, section++, &oobregion);
		if (ret < 0) {
			if (ret != -ERANGE)
				return ret;

			break;
		}

		eccpos = oobregion.offset;
		for (; i < MTD_MAX_ECCPOS_ENTRIES &&
		       eccpos < oobregion.offset + oobregion.length; i++) {
			to->eccpos[i] = eccpos++;
			to->eccbytes++;
		}
	}

	for (i = 0; i < MTD_MAX_OOBFREE_ENTRIES; i++) {
		ret = mtd_ooblayout_free(mtd, i, &oobregion);
		if (ret < 0) {
			if (ret != -ERANGE)
				return ret;

			break;
		}

		to->oobfree[i].offset = oobregion.offset;
		to->oobfree[i].length = oobregion.length;
		to->oobavail += to->oobfree[i].length;
	}

	return 0;
}