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
struct swap_eb {int /*<<< orphan*/ * root; int /*<<< orphan*/  flags; } ;
struct mtdswap_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  mtd; int /*<<< orphan*/  spare_eblks; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBLOCK_BAD ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int mtd_block_markbad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_can_have_bb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtdswap_eb_detach (struct mtdswap_dev*,struct swap_eb*) ; 
 int /*<<< orphan*/  mtdswap_eb_offset (struct mtdswap_dev*,struct swap_eb*) ; 

__attribute__((used)) static int mtdswap_handle_badblock(struct mtdswap_dev *d, struct swap_eb *eb)
{
	int ret;
	loff_t offset;

	d->spare_eblks--;
	eb->flags |= EBLOCK_BAD;
	mtdswap_eb_detach(d, eb);
	eb->root = NULL;

	/* badblocks not supported */
	if (!mtd_can_have_bb(d->mtd))
		return 1;

	offset = mtdswap_eb_offset(d, eb);
	dev_warn(d->dev, "Marking bad block at %08llx\n", offset);
	ret = mtd_block_markbad(d->mtd, offset);

	if (ret) {
		dev_warn(d->dev, "Mark block bad failed for block at %08llx "
			"error %d\n", offset, ret);
		return ret;
	}

	return 1;

}