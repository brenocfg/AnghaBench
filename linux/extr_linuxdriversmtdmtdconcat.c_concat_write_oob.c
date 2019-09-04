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
struct mtd_oob_ops {scalar_t__ retlen; scalar_t__ oobretlen; scalar_t__ len; scalar_t__ datbuf; scalar_t__ oobbuf; scalar_t__ ooblen; } ;
struct mtd_info {int flags; scalar_t__ size; } ;
struct mtd_concat {int num_subdev; struct mtd_info** subdev; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct mtd_concat* CONCAT (struct mtd_info*) ; 
 int EINVAL ; 
 int EROFS ; 
 int MTD_WRITEABLE ; 
 int mtd_write_oob (struct mtd_info*,scalar_t__,struct mtd_oob_ops*) ; 

__attribute__((used)) static int
concat_write_oob(struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops)
{
	struct mtd_concat *concat = CONCAT(mtd);
	struct mtd_oob_ops devops = *ops;
	int i, err;

	if (!(mtd->flags & MTD_WRITEABLE))
		return -EROFS;

	ops->retlen = ops->oobretlen = 0;

	for (i = 0; i < concat->num_subdev; i++) {
		struct mtd_info *subdev = concat->subdev[i];

		if (to >= subdev->size) {
			to -= subdev->size;
			continue;
		}

		/* partial write ? */
		if (to + devops.len > subdev->size)
			devops.len = subdev->size - to;

		err = mtd_write_oob(subdev, to, &devops);
		ops->retlen += devops.retlen;
		ops->oobretlen += devops.oobretlen;
		if (err)
			return err;

		if (devops.datbuf) {
			devops.len = ops->len - ops->retlen;
			if (!devops.len)
				return 0;
			devops.datbuf += devops.retlen;
		}
		if (devops.oobbuf) {
			devops.ooblen = ops->ooblen - ops->oobretlen;
			if (!devops.ooblen)
				return 0;
			devops.oobbuf += devops.oobretlen;
		}
		to = 0;
	}
	return -EINVAL;
}