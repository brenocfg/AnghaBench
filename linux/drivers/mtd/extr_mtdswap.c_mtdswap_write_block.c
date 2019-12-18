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
struct swap_eb {int /*<<< orphan*/  active_count; } ;
struct mtdswap_dev {unsigned int pages_per_eblk; void** revmap; int /*<<< orphan*/  curr_write_pos; int /*<<< orphan*/  dev; int /*<<< orphan*/ * curr_write; struct swap_eb* eb_data; struct mtd_info* mtd; } ;
struct mtd_info {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 int PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 void* PAGE_UNDEF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t,...) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int mtd_write (struct mtd_info*,int,size_t,size_t*,char*) ; 
 int /*<<< orphan*/  mtdswap_enough_free_pages (struct mtdswap_dev*) ; 
 scalar_t__ mtdswap_gc (struct mtdswap_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtdswap_handle_write_error (struct mtdswap_dev*,struct swap_eb*) ; 
 int mtdswap_map_free_block (struct mtdswap_dev*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int mtdswap_write_block(struct mtdswap_dev *d, char *buf,
			unsigned int page, unsigned int *bp, int gc_context)
{
	struct mtd_info *mtd = d->mtd;
	struct swap_eb *eb;
	size_t retlen;
	loff_t writepos;
	int ret;

retry:
	if (!gc_context)
		while (!mtdswap_enough_free_pages(d))
			if (mtdswap_gc(d, 0) > 0)
				return -ENOSPC;

	ret = mtdswap_map_free_block(d, page, bp);
	eb = d->eb_data + (*bp / d->pages_per_eblk);

	if (ret == -EIO || mtd_is_eccerr(ret)) {
		d->curr_write = NULL;
		eb->active_count--;
		d->revmap[*bp] = PAGE_UNDEF;
		goto retry;
	}

	if (ret < 0)
		return ret;

	writepos = (loff_t)*bp << PAGE_SHIFT;
	ret =  mtd_write(mtd, writepos, PAGE_SIZE, &retlen, buf);
	if (ret == -EIO || mtd_is_eccerr(ret)) {
		d->curr_write_pos--;
		eb->active_count--;
		d->revmap[*bp] = PAGE_UNDEF;
		mtdswap_handle_write_error(d, eb);
		goto retry;
	}

	if (ret < 0) {
		dev_err(d->dev, "Write to MTD device failed: %d (%zd written)",
			ret, retlen);
		goto err;
	}

	if (retlen != PAGE_SIZE) {
		dev_err(d->dev, "Short write to MTD device: %zd written",
			retlen);
		ret = -EIO;
		goto err;
	}

	return ret;

err:
	d->curr_write_pos--;
	eb->active_count--;
	d->revmap[*bp] = PAGE_UNDEF;

	return ret;
}