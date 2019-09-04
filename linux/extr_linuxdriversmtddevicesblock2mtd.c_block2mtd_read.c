#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct page {int dummy; } ;
struct mtd_info {struct block2mtd_dev* priv; } ;
struct block2mtd_dev {TYPE_2__* blkdev; } ;
typedef  int loff_t ;
struct TYPE_4__ {TYPE_1__* bd_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ page_address (struct page*) ; 
 struct page* page_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int block2mtd_read(struct mtd_info *mtd, loff_t from, size_t len,
		size_t *retlen, u_char *buf)
{
	struct block2mtd_dev *dev = mtd->priv;
	struct page *page;
	int index = from >> PAGE_SHIFT;
	int offset = from & (PAGE_SIZE-1);
	int cpylen;

	while (len) {
		if ((offset + len) > PAGE_SIZE)
			cpylen = PAGE_SIZE - offset;	// multiple pages
		else
			cpylen = len;	// this page
		len = len - cpylen;

		page = page_read(dev->blkdev->bd_inode->i_mapping, index);
		if (IS_ERR(page))
			return PTR_ERR(page);

		memcpy(buf, page_address(page) + offset, cpylen);
		put_page(page);

		if (retlen)
			*retlen += cpylen;
		buf += cpylen;
		offset = 0;
		index++;
	}
	return 0;
}