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
struct mtd_info {struct map_info* priv; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {scalar_t__ mfr; scalar_t__ id; } ;
struct cfi_fixup {scalar_t__ mfr; scalar_t__ id; int /*<<< orphan*/  (* fixup ) (struct mtd_info*) ;} ;

/* Variables and functions */
 scalar_t__ CFI_ID_ANY ; 
 scalar_t__ CFI_MFR_ANY ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 

void cfi_fixup(struct mtd_info *mtd, struct cfi_fixup *fixups)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	struct cfi_fixup *f;

	for (f=fixups; f->fixup; f++) {
		if (((f->mfr == CFI_MFR_ANY) || (f->mfr == cfi->mfr)) &&
		    ((f->id  == CFI_ID_ANY)  || (f->id  == cfi->id))) {
			f->fixup(mtd);
		}
	}
}