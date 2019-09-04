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
struct swap_eb {scalar_t__ erase_count; } ;
struct mtdswap_dev {scalar_t__ max_erase_count; int /*<<< orphan*/  dev; struct mtd_info* mtd; } ;
struct mtd_info {int /*<<< orphan*/  name; int /*<<< orphan*/  erasesize; } ;
struct erase_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MTDSWAP_ERASE_RETRIES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct erase_info*,int /*<<< orphan*/ ,int) ; 
 int mtd_erase (struct mtd_info*,struct erase_info*) ; 
 int /*<<< orphan*/  mtdswap_eb_offset (struct mtdswap_dev*,struct swap_eb*) ; 
 int /*<<< orphan*/  mtdswap_handle_badblock (struct mtdswap_dev*,struct swap_eb*) ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static int mtdswap_erase_block(struct mtdswap_dev *d, struct swap_eb *eb)
{
	struct mtd_info *mtd = d->mtd;
	struct erase_info erase;
	unsigned int retries = 0;
	int ret;

	eb->erase_count++;
	if (eb->erase_count > d->max_erase_count)
		d->max_erase_count = eb->erase_count;

retry:
	memset(&erase, 0, sizeof(struct erase_info));
	erase.addr	= mtdswap_eb_offset(d, eb);
	erase.len	= mtd->erasesize;

	ret = mtd_erase(mtd, &erase);
	if (ret) {
		if (retries++ < MTDSWAP_ERASE_RETRIES) {
			dev_warn(d->dev,
				"erase of erase block %#llx on %s failed",
				erase.addr, mtd->name);
			yield();
			goto retry;
		}

		dev_err(d->dev, "Cannot erase erase block %#llx on %s\n",
			erase.addr, mtd->name);

		mtdswap_handle_badblock(d, eb);
		return -EIO;
	}

	return 0;
}