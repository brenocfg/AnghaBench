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
struct lpddr_private {int chipshift; int /*<<< orphan*/ * chips; TYPE_1__* qinfo; } ;
struct kvec {scalar_t__ iov_len; } ;
typedef  int loff_t ;
struct TYPE_2__ {int BufSizeShift; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 int do_write_buffer (struct map_info*,int /*<<< orphan*/ *,unsigned long,struct kvec const**,unsigned long*,int) ; 

__attribute__((used)) static int lpddr_writev(struct mtd_info *mtd, const struct kvec *vecs,
				unsigned long count, loff_t to, size_t *retlen)
{
	struct map_info *map = mtd->priv;
	struct lpddr_private *lpddr = map->fldrv_priv;
	int ret = 0;
	int chipnum;
	unsigned long ofs, vec_seek, i;
	int wbufsize = 1 << lpddr->qinfo->BufSizeShift;
	size_t len = 0;

	for (i = 0; i < count; i++)
		len += vecs[i].iov_len;

	if (!len)
		return 0;

	chipnum = to >> lpddr->chipshift;

	ofs = to;
	vec_seek = 0;

	do {
		/* We must not cross write block boundaries */
		int size = wbufsize - (ofs & (wbufsize-1));

		if (size > len)
			size = len;

		ret = do_write_buffer(map, &lpddr->chips[chipnum],
					  ofs, &vecs, &vec_seek, size);
		if (ret)
			return ret;

		ofs += size;
		(*retlen) += size;
		len -= size;

		/* Be nice and reschedule with the chip in a usable
		 * state for other processes */
		cond_resched();

	} while (len);

	return 0;
}