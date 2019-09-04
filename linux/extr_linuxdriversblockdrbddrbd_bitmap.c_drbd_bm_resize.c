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
typedef  unsigned long u64 ;
struct page {int dummy; } ;
struct drbd_device {int /*<<< orphan*/  ldev; struct drbd_bitmap* bitmap; } ;
struct drbd_bitmap {scalar_t__ bm_dev_capacity; unsigned long bm_number_of_pages; unsigned long bm_words; unsigned long bm_set; unsigned long bm_bits; int /*<<< orphan*/  bm_lock; struct page** bm_pages; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,int) ; 
 int /*<<< orphan*/  BM_LOCKED_MASK ; 
 int BM_SECT_PER_BIT ; 
 unsigned long BM_SECT_TO_BIT (unsigned long) ; 
 int /*<<< orphan*/  DRBD_FAULT_BM_ALLOC ; 
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 unsigned long LN2_BPL ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  bm_clear_surplus (struct drbd_bitmap*) ; 
 unsigned long bm_count_bits (struct drbd_bitmap*) ; 
 int /*<<< orphan*/  bm_free_pages (struct page**,unsigned long) ; 
 int /*<<< orphan*/  bm_memset (struct drbd_bitmap*,unsigned long,int,unsigned long) ; 
 struct page** bm_realloc_pages (struct drbd_bitmap*,unsigned long) ; 
 int /*<<< orphan*/  bm_set_surplus (struct drbd_bitmap*) ; 
 int /*<<< orphan*/  bm_vk_free (struct page**) ; 
 int /*<<< orphan*/  drbd_bm_lock (struct drbd_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_bm_unlock (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_info (struct drbd_device*,char*,unsigned long,...) ; 
 scalar_t__ drbd_insert_fault (struct drbd_device*,int /*<<< orphan*/ ) ; 
 unsigned long drbd_md_on_disk_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (struct drbd_bitmap*) ; 
 scalar_t__ get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int drbd_bm_resize(struct drbd_device *device, sector_t capacity, int set_new_bits)
{
	struct drbd_bitmap *b = device->bitmap;
	unsigned long bits, words, owords, obits;
	unsigned long want, have, onpages; /* number of pages */
	struct page **npages, **opages = NULL;
	int err = 0;
	bool growing;

	if (!expect(b))
		return -ENOMEM;

	drbd_bm_lock(device, "resize", BM_LOCKED_MASK);

	drbd_info(device, "drbd_bm_resize called with capacity == %llu\n",
			(unsigned long long)capacity);

	if (capacity == b->bm_dev_capacity)
		goto out;

	if (capacity == 0) {
		spin_lock_irq(&b->bm_lock);
		opages = b->bm_pages;
		onpages = b->bm_number_of_pages;
		owords = b->bm_words;
		b->bm_pages = NULL;
		b->bm_number_of_pages =
		b->bm_set   =
		b->bm_bits  =
		b->bm_words =
		b->bm_dev_capacity = 0;
		spin_unlock_irq(&b->bm_lock);
		bm_free_pages(opages, onpages);
		bm_vk_free(opages);
		goto out;
	}
	bits  = BM_SECT_TO_BIT(ALIGN(capacity, BM_SECT_PER_BIT));

	/* if we would use
	   words = ALIGN(bits,BITS_PER_LONG) >> LN2_BPL;
	   a 32bit host could present the wrong number of words
	   to a 64bit host.
	*/
	words = ALIGN(bits, 64) >> LN2_BPL;

	if (get_ldev(device)) {
		u64 bits_on_disk = drbd_md_on_disk_bits(device->ldev);
		put_ldev(device);
		if (bits > bits_on_disk) {
			drbd_info(device, "bits = %lu\n", bits);
			drbd_info(device, "bits_on_disk = %llu\n", bits_on_disk);
			err = -ENOSPC;
			goto out;
		}
	}

	want = ALIGN(words*sizeof(long), PAGE_SIZE) >> PAGE_SHIFT;
	have = b->bm_number_of_pages;
	if (want == have) {
		D_ASSERT(device, b->bm_pages != NULL);
		npages = b->bm_pages;
	} else {
		if (drbd_insert_fault(device, DRBD_FAULT_BM_ALLOC))
			npages = NULL;
		else
			npages = bm_realloc_pages(b, want);
	}

	if (!npages) {
		err = -ENOMEM;
		goto out;
	}

	spin_lock_irq(&b->bm_lock);
	opages = b->bm_pages;
	owords = b->bm_words;
	obits  = b->bm_bits;

	growing = bits > obits;
	if (opages && growing && set_new_bits)
		bm_set_surplus(b);

	b->bm_pages = npages;
	b->bm_number_of_pages = want;
	b->bm_bits  = bits;
	b->bm_words = words;
	b->bm_dev_capacity = capacity;

	if (growing) {
		if (set_new_bits) {
			bm_memset(b, owords, 0xff, words-owords);
			b->bm_set += bits - obits;
		} else
			bm_memset(b, owords, 0x00, words-owords);

	}

	if (want < have) {
		/* implicit: (opages != NULL) && (opages != npages) */
		bm_free_pages(opages + want, have - want);
	}

	(void)bm_clear_surplus(b);

	spin_unlock_irq(&b->bm_lock);
	if (opages != npages)
		bm_vk_free(opages);
	if (!growing)
		b->bm_set = bm_count_bits(b);
	drbd_info(device, "resync bitmap: bits=%lu words=%lu pages=%lu\n", bits, words, want);

 out:
	drbd_bm_unlock(device);
	return err;
}