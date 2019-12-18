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
struct mtd_oob_ops {scalar_t__ len; size_t ooblen; size_t ooboffs; int /*<<< orphan*/  oobbuf; int /*<<< orphan*/  datbuf; } ;
struct mtd_info {scalar_t__ size; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ mtd_div_by_ws (scalar_t__,struct mtd_info*) ; 
 size_t mtd_oobavail (struct mtd_info*,struct mtd_oob_ops*) ; 

__attribute__((used)) static int mtd_check_oob_ops(struct mtd_info *mtd, loff_t offs,
			     struct mtd_oob_ops *ops)
{
	/*
	 * Some users are setting ->datbuf or ->oobbuf to NULL, but are leaving
	 * ->len or ->ooblen uninitialized. Force ->len and ->ooblen to 0 in
	 *  this case.
	 */
	if (!ops->datbuf)
		ops->len = 0;

	if (!ops->oobbuf)
		ops->ooblen = 0;

	if (offs < 0 || offs + ops->len > mtd->size)
		return -EINVAL;

	if (ops->ooblen) {
		size_t maxooblen;

		if (ops->ooboffs >= mtd_oobavail(mtd, ops))
			return -EINVAL;

		maxooblen = ((size_t)(mtd_div_by_ws(mtd->size, mtd) -
				      mtd_div_by_ws(offs, mtd)) *
			     mtd_oobavail(mtd, ops)) - ops->ooboffs;
		if (ops->ooblen > maxooblen)
			return -EINVAL;
	}

	return 0;
}