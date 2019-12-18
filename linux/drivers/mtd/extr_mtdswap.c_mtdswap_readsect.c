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
struct swap_eb {int /*<<< orphan*/  flags; } ;
struct mtdswap_dev {unsigned int* page_data; unsigned int pages_per_eblk; scalar_t__* revmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  mtd_read_count; struct swap_eb* eb_data; int /*<<< orphan*/  sect_read_count; struct mtd_info* mtd; } ;
struct mtd_info {int dummy; } ;
struct mtd_blktrans_dev {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 unsigned int BLOCK_MAX ; 
 unsigned int BLOCK_UNDEF ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EBLOCK_BITFLIP ; 
 int /*<<< orphan*/  EBLOCK_READERR ; 
 int EIO ; 
 int /*<<< orphan*/  MTDSWAP_BITFLIP ; 
 int /*<<< orphan*/  MTDSWAP_FAILING ; 
 unsigned int MTDSWAP_IO_RETRIES ; 
 struct mtdswap_dev* MTDSWAP_MBD_TO_MTDSWAP (struct mtd_blktrans_dev*) ; 
 int PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 scalar_t__ PAGE_UNDEF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ header ; 
 int /*<<< orphan*/  memset (char*,int,size_t) ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 int mtd_read (struct mtd_info*,int,size_t,size_t*,char*) ; 
 int mtdswap_auto_header (struct mtdswap_dev*,char*) ; 
 int /*<<< orphan*/  mtdswap_rb_add (struct mtdswap_dev*,struct swap_eb*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mtdswap_readsect(struct mtd_blktrans_dev *dev,
			unsigned long page, char *buf)
{
	struct mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	struct mtd_info *mtd = d->mtd;
	unsigned int realblock, retries;
	loff_t readpos;
	struct swap_eb *eb;
	size_t retlen;
	int ret;

	d->sect_read_count++;

	if (header) {
		if (unlikely(page == 0))
			return mtdswap_auto_header(d, buf);

		page--;
	}

	realblock = d->page_data[page];
	if (realblock > BLOCK_MAX) {
		memset(buf, 0x0, PAGE_SIZE);
		if (realblock == BLOCK_UNDEF)
			return 0;
		else
			return -EIO;
	}

	eb = d->eb_data + (realblock / d->pages_per_eblk);
	BUG_ON(d->revmap[realblock] == PAGE_UNDEF);

	readpos = (loff_t)realblock << PAGE_SHIFT;
	retries = 0;

retry:
	ret = mtd_read(mtd, readpos, PAGE_SIZE, &retlen, buf);

	d->mtd_read_count++;
	if (mtd_is_bitflip(ret)) {
		eb->flags |= EBLOCK_BITFLIP;
		mtdswap_rb_add(d, eb, MTDSWAP_BITFLIP);
		ret = 0;
	}

	if (ret < 0) {
		dev_err(d->dev, "Read error %d\n", ret);
		eb->flags |= EBLOCK_READERR;
		mtdswap_rb_add(d, eb, MTDSWAP_FAILING);
		retries++;
		if (retries < MTDSWAP_IO_RETRIES)
			goto retry;

		return ret;
	}

	if (retlen != PAGE_SIZE) {
		dev_err(d->dev, "Short read %zd\n", retlen);
		return -EIO;
	}

	return 0;
}