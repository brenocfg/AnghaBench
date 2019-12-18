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
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int mtd_write_oob (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

int mtd_write(struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen,
	      const u_char *buf)
{
	struct mtd_oob_ops ops = {
		.len = len,
		.datbuf = (u8 *)buf,
	};
	int ret;

	ret = mtd_write_oob(mtd, to, &ops);
	*retlen = ops.retlen;

	return ret;
}