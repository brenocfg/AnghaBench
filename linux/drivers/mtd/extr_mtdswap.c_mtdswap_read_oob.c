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
struct mtdswap_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  mtd; } ;
struct mtd_oob_ops {int /*<<< orphan*/  ooblen; int /*<<< orphan*/  oobretlen; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 int mtd_read_oob (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

__attribute__((used)) static int mtdswap_read_oob(struct mtdswap_dev *d, loff_t from,
			struct mtd_oob_ops *ops)
{
	int ret = mtd_read_oob(d->mtd, from, ops);

	if (mtd_is_bitflip(ret))
		return ret;

	if (ret) {
		dev_warn(d->dev, "Read OOB failed %d for block at %08llx\n",
			ret, from);
		return ret;
	}

	if (ops->oobretlen < ops->ooblen) {
		dev_warn(d->dev, "Read OOB return short read (%zd bytes not "
			"%zd) for block at %08llx\n",
			ops->oobretlen, ops->ooblen, from);
		return -EIO;
	}

	return 0;
}