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
struct mtdswap_dev {unsigned int pages_per_eblk; scalar_t__ oob_buf; scalar_t__ page_buf; struct mtd_info* mtd; } ;
struct mtd_oob_ops {unsigned int len; unsigned int ooblen; scalar_t__ oobbuf; scalar_t__ datbuf; scalar_t__ ooboffs; int /*<<< orphan*/  mode; } ;
struct mtd_info {unsigned int writesize; unsigned int oobavail; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBLOCK_READERR ; 
 int /*<<< orphan*/  MTD_OPS_AUTO_OOB ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  memset (scalar_t__,unsigned int,unsigned int) ; 
 int mtd_read_oob (struct mtd_info*,unsigned int,struct mtd_oob_ops*) ; 
 int mtd_write_oob (struct mtd_info*,unsigned int,struct mtd_oob_ops*) ; 
 unsigned int mtdswap_eb_offset (struct mtdswap_dev*,struct swap_eb*) ; 
 int mtdswap_erase_block (struct mtdswap_dev*,struct swap_eb*) ; 
 int /*<<< orphan*/  mtdswap_handle_badblock (struct mtdswap_dev*,struct swap_eb*) ; 
 unsigned int mtdswap_test_patt (unsigned int) ; 

__attribute__((used)) static unsigned int mtdswap_eblk_passes(struct mtdswap_dev *d,
					struct swap_eb *eb)
{
	struct mtd_info *mtd = d->mtd;
	unsigned int test, i, j, patt, mtd_pages;
	loff_t base, pos;
	unsigned int *p1 = (unsigned int *)d->page_buf;
	unsigned char *p2 = (unsigned char *)d->oob_buf;
	struct mtd_oob_ops ops;
	int ret;

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.len = mtd->writesize;
	ops.ooblen = mtd->oobavail;
	ops.ooboffs = 0;
	ops.datbuf = d->page_buf;
	ops.oobbuf = d->oob_buf;
	base = mtdswap_eb_offset(d, eb);
	mtd_pages = d->pages_per_eblk * PAGE_SIZE / mtd->writesize;

	for (test = 0; test < 2; test++) {
		pos = base;
		for (i = 0; i < mtd_pages; i++) {
			patt = mtdswap_test_patt(test + i);
			memset(d->page_buf, patt, mtd->writesize);
			memset(d->oob_buf, patt, mtd->oobavail);
			ret = mtd_write_oob(mtd, pos, &ops);
			if (ret)
				goto error;

			pos += mtd->writesize;
		}

		pos = base;
		for (i = 0; i < mtd_pages; i++) {
			ret = mtd_read_oob(mtd, pos, &ops);
			if (ret)
				goto error;

			patt = mtdswap_test_patt(test + i);
			for (j = 0; j < mtd->writesize/sizeof(int); j++)
				if (p1[j] != patt)
					goto error;

			for (j = 0; j < mtd->oobavail; j++)
				if (p2[j] != (unsigned char)patt)
					goto error;

			pos += mtd->writesize;
		}

		ret = mtdswap_erase_block(d, eb);
		if (ret)
			goto error;
	}

	eb->flags &= ~EBLOCK_READERR;
	return 1;

error:
	mtdswap_handle_badblock(d, eb);
	return 0;
}