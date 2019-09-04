#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtd_oob_ops {scalar_t__ len; scalar_t__ retlen; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/  datbuf; scalar_t__ ooboffs; scalar_t__ oobretlen; scalar_t__ ooblen; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {scalar_t__ writesize; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MTD_OPS_RAW ; 
 TYPE_1__* mtd ; 
 int mtd_write_oob (TYPE_1__*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 int /*<<< orphan*/  offset ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  wbuffer ; 

__attribute__((used)) static int rewrite_page(int log)
{
	int err = 0;
	struct mtd_oob_ops ops;

	if (log)
		pr_info("rewrite page\n");

	ops.mode      = MTD_OPS_RAW; /* No ECC */
	ops.len       = mtd->writesize;
	ops.retlen    = 0;
	ops.ooblen    = 0;
	ops.oobretlen = 0;
	ops.ooboffs   = 0;
	ops.datbuf    = wbuffer;
	ops.oobbuf    = NULL;

	err = mtd_write_oob(mtd, offset, &ops);
	if (err || ops.retlen != mtd->writesize) {
		pr_err("error: write_oob failed (%d)\n", err);
		if (!err)
			err = -EIO;
	}

	return err;
}