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

__attribute__((used)) static int hwecc4_ooblayout_small_free(struct mtd_info *mtd, int section,
				       struct mtd_oob_region *oobregion)
{
	if (section > 1)
		return -ERANGE;

	if (!section) {
		oobregion->offset = 8;
		oobregion->length = 5;
	} else {
		oobregion->offset = 16;
		oobregion->length = mtd->oobsize - 16;
	}

	return 0;
}