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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  u8 ;
struct mtd_oob_ops {size_t len; size_t retlen; int /*<<< orphan*/ * datbuf; } ;
struct mtd_info {scalar_t__ size; int (* _write ) (struct mtd_info*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ;int (* _write_oob ) (struct mtd_info*,scalar_t__,struct mtd_oob_ops*) ;int flags; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 int MTD_WRITEABLE ; 
 int /*<<< orphan*/  ledtrig_mtd_activity () ; 
 int stub1 (struct mtd_info*,scalar_t__,struct mtd_oob_ops*) ; 
 int stub2 (struct mtd_info*,scalar_t__,size_t,size_t*,int /*<<< orphan*/  const*) ; 

int mtd_write(struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen,
	      const u_char *buf)
{
	*retlen = 0;
	if (to < 0 || to >= mtd->size || len > mtd->size - to)
		return -EINVAL;
	if ((!mtd->_write && !mtd->_write_oob) ||
	    !(mtd->flags & MTD_WRITEABLE))
		return -EROFS;
	if (!len)
		return 0;
	ledtrig_mtd_activity();

	if (!mtd->_write) {
		struct mtd_oob_ops ops = {
			.len = len,
			.datbuf = (u8 *)buf,
		};
		int ret;

		ret = mtd->_write_oob(mtd, to, &ops);
		*retlen = ops.retlen;
		return ret;
	}

	return mtd->_write(mtd, to, len, retlen, buf);
}