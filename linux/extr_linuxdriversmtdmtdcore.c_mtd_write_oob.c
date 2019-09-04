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
struct mtd_oob_ops {int /*<<< orphan*/  datbuf; scalar_t__ retlen; int /*<<< orphan*/  len; scalar_t__ oobbuf; scalar_t__ oobretlen; } ;
struct mtd_info {int flags; int (* _write_oob ) (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ;int (* _write ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EROFS ; 
 int MTD_WRITEABLE ; 
 int /*<<< orphan*/  ledtrig_mtd_activity () ; 
 int mtd_check_oob_ops (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 int stub2 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

int mtd_write_oob(struct mtd_info *mtd, loff_t to,
				struct mtd_oob_ops *ops)
{
	int ret;

	ops->retlen = ops->oobretlen = 0;

	if (!(mtd->flags & MTD_WRITEABLE))
		return -EROFS;

	ret = mtd_check_oob_ops(mtd, to, ops);
	if (ret)
		return ret;

	ledtrig_mtd_activity();

	/* Check the validity of a potential fallback on mtd->_write */
	if (!mtd->_write_oob && (!mtd->_write || ops->oobbuf))
		return -EOPNOTSUPP;

	if (mtd->_write_oob)
		return mtd->_write_oob(mtd, to, ops);
	else
		return mtd->_write(mtd, to, ops->len, &ops->retlen,
				   ops->datbuf);
}