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
typedef  int (* varsize_frob_t ) (struct map_info*,int /*<<< orphan*/ *,unsigned long,int,void*) ;
struct mtd_info {int numeraseregions; struct mtd_erase_region_info* eraseregions; struct map_info* priv; } ;
struct mtd_erase_region_info {int offset; int erasesize; int numblocks; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {int chipshift; int numchips; int /*<<< orphan*/ * chips; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct map_info*,int /*<<< orphan*/ *,unsigned long,int,void*) ; 

int cfi_varsize_frob(struct mtd_info *mtd, varsize_frob_t frob,
				     loff_t ofs, size_t len, void *thunk)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	unsigned long adr;
	int chipnum, ret = 0;
	int i, first;
	struct mtd_erase_region_info *regions = mtd->eraseregions;

	/* Check that both start and end of the requested erase are
	 * aligned with the erasesize at the appropriate addresses.
	 */

	i = 0;

	/* Skip all erase regions which are ended before the start of
	   the requested erase. Actually, to save on the calculations,
	   we skip to the first erase region which starts after the
	   start of the requested erase, and then go back one.
	*/

	while (i < mtd->numeraseregions && ofs >= regions[i].offset)
	       i++;
	i--;

	/* OK, now i is pointing at the erase region in which this
	   erase request starts. Check the start of the requested
	   erase range is aligned with the erase size which is in
	   effect here.
	*/

	if (ofs & (regions[i].erasesize-1))
		return -EINVAL;

	/* Remember the erase region we start on */
	first = i;

	/* Next, check that the end of the requested erase is aligned
	 * with the erase region at that address.
	 */

	while (i<mtd->numeraseregions && (ofs + len) >= regions[i].offset)
		i++;

	/* As before, drop back one to point at the region in which
	   the address actually falls
	*/
	i--;

	if ((ofs + len) & (regions[i].erasesize-1))
		return -EINVAL;

	chipnum = ofs >> cfi->chipshift;
	adr = ofs - (chipnum << cfi->chipshift);

	i=first;

	while(len) {
		int size = regions[i].erasesize;

		ret = (*frob)(map, &cfi->chips[chipnum], adr, size, thunk);

		if (ret)
			return ret;

		adr += size;
		ofs += size;
		len -= size;

		if (ofs == regions[i].offset + size * regions[i].numblocks)
			i++;

		if (adr >> cfi->chipshift) {
			adr = 0;
			chipnum++;

			if (chipnum >= cfi->numchips)
				break;
		}
	}

	return 0;
}