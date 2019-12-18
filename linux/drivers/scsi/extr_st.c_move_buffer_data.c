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
struct st_buffer {int reserved_page_order; int buffer_bytes; int frp_segs; int read_pointer; struct page** reserved_pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int min (int,int) ; 
 scalar_t__ page_address (struct page*) ; 

__attribute__((used)) static void move_buffer_data(struct st_buffer * st_bp, int offset)
{
	int src_seg, dst_seg, src_offset = 0, dst_offset;
	int count, total;
	int length = PAGE_SIZE << st_bp->reserved_page_order;

	if (offset == 0)
		return;

	total=st_bp->buffer_bytes - offset;
	for (src_seg=0; src_seg < st_bp->frp_segs; src_seg++) {
		src_offset = offset;
		if (src_offset < length)
			break;
		offset -= length;
	}

	st_bp->buffer_bytes = st_bp->read_pointer = total;
	for (dst_seg=dst_offset=0; total > 0; ) {
		struct page *dpage = st_bp->reserved_pages[dst_seg];
		struct page *spage = st_bp->reserved_pages[src_seg];

		count = min(length - dst_offset, length - src_offset);
		memmove(page_address(dpage) + dst_offset,
			page_address(spage) + src_offset, count);
		src_offset += count;
		if (src_offset >= length) {
			src_seg++;
			src_offset = 0;
		}
		dst_offset += count;
		if (dst_offset >= length) {
			dst_seg++;
			dst_offset = 0;
		}
		total -= count;
	}
}