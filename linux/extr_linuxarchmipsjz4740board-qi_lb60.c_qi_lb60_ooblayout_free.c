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
struct mtd_oob_region {int offset; int length; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int ERANGE ; 

__attribute__((used)) static int qi_lb60_ooblayout_free(struct mtd_info *mtd, int section,
				  struct mtd_oob_region *oobregion)
{
	int eccbytes = 36, eccoff = 6;

	if (section > 1)
		return -ERANGE;

	if (mtd->oobsize == 128) {
		eccbytes *= 2;
		eccoff *= 2;
	}

	if (!section) {
		oobregion->offset = 2;
		oobregion->length = eccoff - 2;
	} else {
		oobregion->offset = eccoff + eccbytes;
		oobregion->length = mtd->oobsize - oobregion->offset;
	}

	return 0;
}