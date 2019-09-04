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
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int ERANGE ; 

__attribute__((used)) static int qi_lb60_ooblayout_ecc(struct mtd_info *mtd, int section,
				 struct mtd_oob_region *oobregion)
{
	if (section)
		return -ERANGE;

	oobregion->length = 36;
	oobregion->offset = 6;

	if (mtd->oobsize == 128) {
		oobregion->length *= 2;
		oobregion->offset *= 2;
	}

	return 0;
}