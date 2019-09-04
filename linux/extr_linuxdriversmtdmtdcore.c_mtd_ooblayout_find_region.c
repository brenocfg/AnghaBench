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
struct mtd_oob_region {int length; int offset; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mtd_oob_region*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtd_ooblayout_find_region(struct mtd_info *mtd, int byte,
				int *sectionp, struct mtd_oob_region *oobregion,
				int (*iter)(struct mtd_info *,
					    int section,
					    struct mtd_oob_region *oobregion))
{
	int pos = 0, ret, section = 0;

	memset(oobregion, 0, sizeof(*oobregion));

	while (1) {
		ret = iter(mtd, section, oobregion);
		if (ret)
			return ret;

		if (pos + oobregion->length > byte)
			break;

		pos += oobregion->length;
		section++;
	}

	/*
	 * Adjust region info to make it start at the beginning at the
	 * 'start' ECC byte.
	 */
	oobregion->offset += byte - pos;
	oobregion->length -= byte - pos;
	*sectionp = section;

	return 0;
}