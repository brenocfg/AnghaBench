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
struct mtd_part {int /*<<< orphan*/  parent; } ;
struct mtd_oob_region {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int mtd_ooblayout_ecc (int /*<<< orphan*/ ,int,struct mtd_oob_region*) ; 
 struct mtd_part* mtd_to_part (struct mtd_info*) ; 

__attribute__((used)) static int part_ooblayout_ecc(struct mtd_info *mtd, int section,
			      struct mtd_oob_region *oobregion)
{
	struct mtd_part *part = mtd_to_part(mtd);

	return mtd_ooblayout_ecc(part->parent, section, oobregion);
}