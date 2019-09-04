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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_info {struct map_info* priv; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct cfi_private {int chipshift; int numchips; int /*<<< orphan*/ * chips; TYPE_1__* cfiq; } ;
typedef  int loff_t ;
struct TYPE_2__ {int MaxBufWriteSize; } ;

/* Variables and functions */
 int cfi_interleave (struct cfi_private*) ; 
 int do_write_buffer (struct map_info*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int cfi_staa_write_buffers (struct mtd_info *mtd, loff_t to,
				       size_t len, size_t *retlen, const u_char *buf)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	int wbufsize = cfi_interleave(cfi) << cfi->cfiq->MaxBufWriteSize;
	int ret = 0;
	int chipnum;
	unsigned long ofs;

	chipnum = to >> cfi->chipshift;
	ofs = to  - (chipnum << cfi->chipshift);

#ifdef DEBUG_CFI_FEATURES
	printk("%s: map_bankwidth(map)[%x]\n", __func__, map_bankwidth(map));
	printk("%s: chipnum[%x] wbufsize[%x]\n", __func__, chipnum, wbufsize);
	printk("%s: ofs[%x] len[%x]\n", __func__, ofs, len);
#endif

        /* Write buffer is worth it only if more than one word to write... */
        while (len > 0) {
		/* We must not cross write block boundaries */
		int size = wbufsize - (ofs & (wbufsize-1));

                if (size > len)
                    size = len;

                ret = do_write_buffer(map, &cfi->chips[chipnum],
				      ofs, buf, size);
		if (ret)
			return ret;

		ofs += size;
		buf += size;
		(*retlen) += size;
		len -= size;

		if (ofs >> cfi->chipshift) {
			chipnum ++;
			ofs = 0;
			if (chipnum == cfi->numchips)
				return 0;
		}
	}

	return 0;
}