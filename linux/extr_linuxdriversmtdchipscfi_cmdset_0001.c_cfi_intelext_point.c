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
struct map_info {scalar_t__ phys; void* virt; struct cfi_private* fldrv_priv; } ;
struct cfi_private {int chipshift; int numchips; TYPE_1__* chips; } ;
typedef  scalar_t__ resource_size_t ;
typedef  int loff_t ;
struct TYPE_2__ {long start; } ;

/* Variables and functions */
 int EINVAL ; 
 int do_point_onechip (struct map_info*,TYPE_1__*,unsigned long,unsigned long) ; 

__attribute__((used)) static int cfi_intelext_point(struct mtd_info *mtd, loff_t from, size_t len,
		size_t *retlen, void **virt, resource_size_t *phys)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	unsigned long ofs, last_end = 0;
	int chipnum;
	int ret = 0;

	if (!map->virt)
		return -EINVAL;

	/* Now lock the chip(s) to POINT state */

	/* ofs: offset within the first chip that the first read should start */
	chipnum = (from >> cfi->chipshift);
	ofs = from - (chipnum << cfi->chipshift);

	*virt = map->virt + cfi->chips[chipnum].start + ofs;
	if (phys)
		*phys = map->phys + cfi->chips[chipnum].start + ofs;

	while (len) {
		unsigned long thislen;

		if (chipnum >= cfi->numchips)
			break;

		/* We cannot point across chips that are virtually disjoint */
		if (!last_end)
			last_end = cfi->chips[chipnum].start;
		else if (cfi->chips[chipnum].start != last_end)
			break;

		if ((len + ofs -1) >> cfi->chipshift)
			thislen = (1<<cfi->chipshift) - ofs;
		else
			thislen = len;

		ret = do_point_onechip(map, &cfi->chips[chipnum], ofs, thislen);
		if (ret)
			break;

		*retlen += thislen;
		len -= thislen;

		ofs = 0;
		last_end += 1 << cfi->chipshift;
		chipnum++;
	}
	return 0;
}