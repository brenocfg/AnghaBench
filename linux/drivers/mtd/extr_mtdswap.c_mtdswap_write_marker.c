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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u16 ;
struct swap_eb {int /*<<< orphan*/  erase_count; } ;
struct mtdswap_oobdata {void* magic; int /*<<< orphan*/  count; } ;
struct mtdswap_dev {int /*<<< orphan*/  dev; TYPE_1__* mtd; } ;
struct mtd_oob_ops {int ooblen; int oobretlen; int /*<<< orphan*/ * datbuf; int /*<<< orphan*/  mode; int /*<<< orphan*/ * oobbuf; scalar_t__ ooboffs; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ writesize; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MTDSWAP_MAGIC_CLEAN ; 
 int /*<<< orphan*/  MTDSWAP_MAGIC_DIRTY ; 
 int MTDSWAP_OOBSIZE ; 
 scalar_t__ MTDSWAP_TYPE_CLEAN ; 
 int /*<<< orphan*/  MTD_OPS_AUTO_OOB ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,int,...) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int mtd_write_oob (TYPE_1__*,scalar_t__,struct mtd_oob_ops*) ; 
 scalar_t__ mtdswap_eb_offset (struct mtdswap_dev*,struct swap_eb*) ; 
 int /*<<< orphan*/  mtdswap_handle_write_error (struct mtdswap_dev*,struct swap_eb*) ; 

__attribute__((used)) static int mtdswap_write_marker(struct mtdswap_dev *d, struct swap_eb *eb,
				u16 marker)
{
	struct mtdswap_oobdata n;
	int ret;
	loff_t offset;
	struct mtd_oob_ops ops;

	ops.ooboffs = 0;
	ops.oobbuf = (uint8_t *)&n;
	ops.mode = MTD_OPS_AUTO_OOB;
	ops.datbuf = NULL;

	if (marker == MTDSWAP_TYPE_CLEAN) {
		n.magic = cpu_to_le16(MTDSWAP_MAGIC_CLEAN);
		n.count = cpu_to_le32(eb->erase_count);
		ops.ooblen = MTDSWAP_OOBSIZE;
		offset = mtdswap_eb_offset(d, eb);
	} else {
		n.magic = cpu_to_le16(MTDSWAP_MAGIC_DIRTY);
		ops.ooblen = sizeof(n.magic);
		offset = mtdswap_eb_offset(d, eb) + d->mtd->writesize;
	}

	ret = mtd_write_oob(d->mtd, offset, &ops);

	if (ret) {
		dev_warn(d->dev, "Write OOB failed for block at %08llx "
			"error %d\n", offset, ret);
		if (ret == -EIO || mtd_is_eccerr(ret))
			mtdswap_handle_write_error(d, eb);
		return ret;
	}

	if (ops.oobretlen != ops.ooblen) {
		dev_warn(d->dev, "Short OOB write for block at %08llx: "
			"%zd not %zd\n",
			offset, ops.oobretlen, ops.ooblen);
		return ret;
	}

	return 0;
}