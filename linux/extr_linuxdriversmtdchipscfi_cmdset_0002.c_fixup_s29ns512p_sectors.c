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
struct mtd_info {int /*<<< orphan*/  name; struct map_info* priv; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {TYPE_1__* cfiq; } ;
struct TYPE_2__ {int* EraseRegionInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fixup_s29ns512p_sectors(struct mtd_info *mtd)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;

	/*
	 *  S29NS512P flash uses more than 8bits to report number of sectors,
	 * which is not permitted by CFI.
	 */
	cfi->cfiq->EraseRegionInfo[0] = 0x020001ff;
	pr_warn("%s: Bad S29NS512P CFI data; adjust to 512 sectors\n",
		mtd->name);
}