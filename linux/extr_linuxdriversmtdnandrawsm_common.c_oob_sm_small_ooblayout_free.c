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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 

__attribute__((used)) static int oob_sm_small_ooblayout_free(struct mtd_info *mtd, int section,
				       struct mtd_oob_region *oobregion)
{
	switch (section) {
	case 0:
		/* reserved */
		oobregion->offset = 3;
		oobregion->length = 2;
		break;
	case 1:
		/* LBA1 */
		oobregion->offset = 6;
		oobregion->length = 2;
		break;
	default:
		return -ERANGE;
	}

	return 0;
}