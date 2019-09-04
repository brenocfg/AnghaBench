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
typedef  int /*<<< orphan*/  u8 ;
struct mtd_oob_ops {scalar_t__ ooblen; scalar_t__ oobretlen; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/  mode; } ;
struct mtd_info {scalar_t__ oobsize; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OPS_PLACE_OOB ; 
 int mtd_read_oob (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

__attribute__((used)) static int sharpsl_nand_read_oob(struct mtd_info *mtd, loff_t offs, u8 *buf)
{
	struct mtd_oob_ops ops = { };
	int ret;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooblen = mtd->oobsize;
	ops.oobbuf = buf;

	ret = mtd_read_oob(mtd, offs, &ops);
	if (ret != 0 || mtd->oobsize != ops.oobretlen)
		return -1;

	return 0;
}