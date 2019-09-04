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
struct page {scalar_t__ index; } ;
struct bitmap_storage {unsigned long file_pages; } ;
struct TYPE_2__ {unsigned long chunkshift; } ;
struct bitmap {unsigned long cluster_slot; scalar_t__ allclean; int /*<<< orphan*/  flags; struct bitmap_storage storage; int /*<<< orphan*/  mddev; TYPE_1__ counts; } ;
typedef  unsigned long sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_HOSTENDIAN ; 
 int /*<<< orphan*/  BITMAP_PAGE_NEEDWRITE ; 
 int /*<<< orphan*/  BITMAP_PAGE_PENDING ; 
 int /*<<< orphan*/  clear_bit (unsigned long,void*) ; 
 int /*<<< orphan*/  clear_bit_le (unsigned long,void*) ; 
 unsigned long file_page_offset (struct bitmap_storage*,unsigned long) ; 
 struct page* filemap_get_page (struct bitmap_storage*,unsigned long) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 scalar_t__ mddev_is_clustered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_attr (struct bitmap*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_page_attr (struct bitmap*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void md_bitmap_file_clear_bit(struct bitmap *bitmap, sector_t block)
{
	unsigned long bit;
	struct page *page;
	void *paddr;
	unsigned long chunk = block >> bitmap->counts.chunkshift;
	struct bitmap_storage *store = &bitmap->storage;
	unsigned long node_offset = 0;

	if (mddev_is_clustered(bitmap->mddev))
		node_offset = bitmap->cluster_slot * store->file_pages;

	page = filemap_get_page(&bitmap->storage, chunk);
	if (!page)
		return;
	bit = file_page_offset(&bitmap->storage, chunk);
	paddr = kmap_atomic(page);
	if (test_bit(BITMAP_HOSTENDIAN, &bitmap->flags))
		clear_bit(bit, paddr);
	else
		clear_bit_le(bit, paddr);
	kunmap_atomic(paddr);
	if (!test_page_attr(bitmap, page->index - node_offset, BITMAP_PAGE_NEEDWRITE)) {
		set_page_attr(bitmap, page->index - node_offset, BITMAP_PAGE_PENDING);
		bitmap->allclean = 0;
	}
}