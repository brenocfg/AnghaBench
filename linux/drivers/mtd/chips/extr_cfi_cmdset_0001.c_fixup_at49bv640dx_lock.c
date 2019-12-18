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
struct mtd_info {int /*<<< orphan*/  flags; struct map_info* priv; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {struct cfi_pri_intelext* cmdset_priv; } ;
struct cfi_pri_intelext {int FeatureSupport; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_POWERUP_LOCK ; 

__attribute__((used)) static void fixup_at49bv640dx_lock(struct mtd_info *mtd)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	struct cfi_pri_intelext *cfip = cfi->cmdset_priv;

	cfip->FeatureSupport |= (1 << 5);
	mtd->flags |= MTD_POWERUP_LOCK;
}