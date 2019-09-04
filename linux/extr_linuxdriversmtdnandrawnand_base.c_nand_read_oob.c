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
struct mtd_oob_ops {scalar_t__ mode; int /*<<< orphan*/  datbuf; scalar_t__ retlen; } ;
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  FL_READING ; 
 scalar_t__ MTD_OPS_AUTO_OOB ; 
 scalar_t__ MTD_OPS_PLACE_OOB ; 
 scalar_t__ MTD_OPS_RAW ; 
 int nand_do_read_oob (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 int nand_do_read_ops (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 int /*<<< orphan*/  nand_get_device (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release_device (struct mtd_info*) ; 

__attribute__((used)) static int nand_read_oob(struct mtd_info *mtd, loff_t from,
			 struct mtd_oob_ops *ops)
{
	int ret;

	ops->retlen = 0;

	if (ops->mode != MTD_OPS_PLACE_OOB &&
	    ops->mode != MTD_OPS_AUTO_OOB &&
	    ops->mode != MTD_OPS_RAW)
		return -ENOTSUPP;

	nand_get_device(mtd, FL_READING);

	if (!ops->datbuf)
		ret = nand_do_read_oob(mtd, from, ops);
	else
		ret = nand_do_read_ops(mtd, from, ops);

	nand_release_device(mtd);
	return ret;
}