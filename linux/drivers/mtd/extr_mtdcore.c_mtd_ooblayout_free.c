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
struct mtd_oob_region {int dummy; } ;
struct mtd_info {TYPE_1__* ooblayout; } ;
struct TYPE_2__ {int (* free ) (struct mtd_info*,int,struct mtd_oob_region*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  memset (struct mtd_oob_region*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct mtd_info*,int,struct mtd_oob_region*) ; 

int mtd_ooblayout_free(struct mtd_info *mtd, int section,
		       struct mtd_oob_region *oobfree)
{
	memset(oobfree, 0, sizeof(*oobfree));

	if (!mtd || section < 0)
		return -EINVAL;

	if (!mtd->ooblayout || !mtd->ooblayout->free)
		return -ENOTSUPP;

	return mtd->ooblayout->free(mtd, section, oobfree);
}