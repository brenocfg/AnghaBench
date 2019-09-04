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
struct page {int dummy; } ;
struct bitmap_storage {int file_pages; unsigned long bytes; int /*<<< orphan*/  filemap_attr; TYPE_1__** filemap; TYPE_1__* sb_page; } ;
typedef  int /*<<< orphan*/  bitmap_super_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int __GFP_ZERO ; 
 void* alloc_page (int) ; 
 TYPE_1__** kmalloc_array (unsigned long,int,int) ; 
 int /*<<< orphan*/  kzalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roundup (unsigned long,int) ; 

__attribute__((used)) static int md_bitmap_storage_alloc(struct bitmap_storage *store,
				   unsigned long chunks, int with_super,
				   int slot_number)
{
	int pnum, offset = 0;
	unsigned long num_pages;
	unsigned long bytes;

	bytes = DIV_ROUND_UP(chunks, 8);
	if (with_super)
		bytes += sizeof(bitmap_super_t);

	num_pages = DIV_ROUND_UP(bytes, PAGE_SIZE);
	offset = slot_number * num_pages;

	store->filemap = kmalloc_array(num_pages, sizeof(struct page *),
				       GFP_KERNEL);
	if (!store->filemap)
		return -ENOMEM;

	if (with_super && !store->sb_page) {
		store->sb_page = alloc_page(GFP_KERNEL|__GFP_ZERO);
		if (store->sb_page == NULL)
			return -ENOMEM;
	}

	pnum = 0;
	if (store->sb_page) {
		store->filemap[0] = store->sb_page;
		pnum = 1;
		store->sb_page->index = offset;
	}

	for ( ; pnum < num_pages; pnum++) {
		store->filemap[pnum] = alloc_page(GFP_KERNEL|__GFP_ZERO);
		if (!store->filemap[pnum]) {
			store->file_pages = pnum;
			return -ENOMEM;
		}
		store->filemap[pnum]->index = pnum + offset;
	}
	store->file_pages = pnum;

	/* We need 4 bits per page, rounded up to a multiple
	 * of sizeof(unsigned long) */
	store->filemap_attr = kzalloc(
		roundup(DIV_ROUND_UP(num_pages*4, 8), sizeof(unsigned long)),
		GFP_KERNEL);
	if (!store->filemap_attr)
		return -ENOMEM;

	store->bytes = bytes;

	return 0;
}