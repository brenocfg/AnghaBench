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
struct map_info {struct lpddr_private* fldrv_priv; } ;
struct lpddr_private {TYPE_1__* qinfo; } ;
struct erase_info {unsigned long addr; unsigned long len; } ;
struct TYPE_2__ {int UniformBlockSizeShift; } ;

/* Variables and functions */
 int do_erase_oneblock (struct mtd_info*,unsigned long) ; 

__attribute__((used)) static int lpddr_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	unsigned long ofs, len;
	int ret;
	struct map_info *map = mtd->priv;
	struct lpddr_private *lpddr = map->fldrv_priv;
	int size = 1 << lpddr->qinfo->UniformBlockSizeShift;

	ofs = instr->addr;
	len = instr->len;

	while (len > 0) {
		ret = do_erase_oneblock(mtd, ofs);
		if (ret)
			return ret;
		ofs += size;
		len -= size;
	}

	return 0;
}