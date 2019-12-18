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

__attribute__((used)) static int onenand_ooblayout_128_free(struct mtd_info *mtd, int section,
				      struct mtd_oob_region *oobregion)
{
	if (section >= 8)
		return -ERANGE;

	/*
	 * free bytes are using the spare area fields marked as
	 * "Managed by internal ECC logic for Logical Sector Number area"
	 */
	oobregion->offset = (section * 16) + 2;
	oobregion->length = 3;

	return 0;
}