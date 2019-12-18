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
struct page_list {int /*<<< orphan*/  page; } ;
struct dm_integrity_c {int log2_blocks_per_bitmap_bit; TYPE_1__* sb; } ;
typedef  int sector_t ;
struct TYPE_2__ {int log2_sectors_per_block; } ;

/* Variables and functions */
 int BITMAP_OP_CLEAR ; 
 int BITMAP_OP_SET ; 
 int BITMAP_OP_TEST_ALL_CLEAR ; 
 int BITMAP_OP_TEST_ALL_SET ; 
 unsigned long BITS_PER_LONG ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DMCRIT (char*,unsigned long long,unsigned long long,int,int,int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __clear_bit (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  __set_bit (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  clear_page (unsigned long*) ; 
 unsigned long* lowmem_page_address (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned long,unsigned long*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool block_bitmap_op(struct dm_integrity_c *ic, struct page_list *bitmap,
			    sector_t sector, sector_t n_sectors, int mode)
{
	unsigned long bit, end_bit, this_end_bit, page, end_page;
	unsigned long *data;

	if (unlikely(((sector | n_sectors) & ((1 << ic->sb->log2_sectors_per_block) - 1)) != 0)) {
		DMCRIT("invalid bitmap access (%llx,%llx,%d,%d,%d)",
			(unsigned long long)sector,
			(unsigned long long)n_sectors,
			ic->sb->log2_sectors_per_block,
			ic->log2_blocks_per_bitmap_bit,
			mode);
		BUG();
	}

	if (unlikely(!n_sectors))
		return true;

	bit = sector >> (ic->sb->log2_sectors_per_block + ic->log2_blocks_per_bitmap_bit);
	end_bit = (sector + n_sectors - 1) >>
		(ic->sb->log2_sectors_per_block + ic->log2_blocks_per_bitmap_bit);

	page = bit / (PAGE_SIZE * 8);
	bit %= PAGE_SIZE * 8;

	end_page = end_bit / (PAGE_SIZE * 8);
	end_bit %= PAGE_SIZE * 8;

repeat:
	if (page < end_page) {
		this_end_bit = PAGE_SIZE * 8 - 1;
	} else {
		this_end_bit = end_bit;
	}

	data = lowmem_page_address(bitmap[page].page);

	if (mode == BITMAP_OP_TEST_ALL_SET) {
		while (bit <= this_end_bit) {
			if (!(bit % BITS_PER_LONG) && this_end_bit >= bit + BITS_PER_LONG - 1) {
				do {
					if (data[bit / BITS_PER_LONG] != -1)
						return false;
					bit += BITS_PER_LONG;
				} while (this_end_bit >= bit + BITS_PER_LONG - 1);
				continue;
			}
			if (!test_bit(bit, data))
				return false;
			bit++;
		}
	} else if (mode == BITMAP_OP_TEST_ALL_CLEAR) {
		while (bit <= this_end_bit) {
			if (!(bit % BITS_PER_LONG) && this_end_bit >= bit + BITS_PER_LONG - 1) {
				do {
					if (data[bit / BITS_PER_LONG] != 0)
						return false;
					bit += BITS_PER_LONG;
				} while (this_end_bit >= bit + BITS_PER_LONG - 1);
				continue;
			}
			if (test_bit(bit, data))
				return false;
			bit++;
		}
	} else if (mode == BITMAP_OP_SET) {
		while (bit <= this_end_bit) {
			if (!(bit % BITS_PER_LONG) && this_end_bit >= bit + BITS_PER_LONG - 1) {
				do {
					data[bit / BITS_PER_LONG] = -1;
					bit += BITS_PER_LONG;
				} while (this_end_bit >= bit + BITS_PER_LONG - 1);
				continue;
			}
			__set_bit(bit, data);
			bit++;
		}
	} else if (mode == BITMAP_OP_CLEAR) {
		if (!bit && this_end_bit == PAGE_SIZE * 8 - 1)
			clear_page(data);
		else while (bit <= this_end_bit) {
			if (!(bit % BITS_PER_LONG) && this_end_bit >= bit + BITS_PER_LONG - 1) {
				do {
					data[bit / BITS_PER_LONG] = 0;
					bit += BITS_PER_LONG;
				} while (this_end_bit >= bit + BITS_PER_LONG - 1);
				continue;
			}
			__clear_bit(bit, data);
			bit++;
		}
	} else {
		BUG();
	}

	if (unlikely(page < end_page)) {
		bit = 0;
		page++;
		goto repeat;
	}

	return true;
}