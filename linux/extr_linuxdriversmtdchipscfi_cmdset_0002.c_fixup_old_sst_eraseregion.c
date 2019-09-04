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
struct mtd_info {struct map_info* priv; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {TYPE_1__* cfiq; } ;
struct TYPE_2__ {int NumEraseRegions; } ;

/* Variables and functions */

__attribute__((used)) static void fixup_old_sst_eraseregion(struct mtd_info *mtd)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;

	/*
	 * These flashes report two separate eraseblock regions based on the
	 * sector_erase-size and block_erase-size, although they both operate on the
	 * same memory. This is not allowed according to CFI, so we just pick the
	 * sector_erase-size.
	 */
	cfi->cfiq->NumEraseRegions = 1;
}