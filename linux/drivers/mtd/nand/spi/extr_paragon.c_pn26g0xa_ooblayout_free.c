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

__attribute__((used)) static int pn26g0xa_ooblayout_free(struct mtd_info *mtd, int section,
				   struct mtd_oob_region *region)
{
	if (section > 4)
		return -ERANGE;

	if (section == 4) {
		region->offset = 64;
		region->length = 64;
	} else {
		region->offset = 4 + (15 * section);
		region->length = 2;
	}

	return 0;
}