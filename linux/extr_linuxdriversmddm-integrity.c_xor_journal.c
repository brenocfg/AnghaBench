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
struct page_list {struct page* page; } ;
struct page {int dummy; } ;
struct journal_completion {int /*<<< orphan*/  in_flight; } ;
struct dm_integrity_c {unsigned int journal_section_sectors; TYPE_1__* journal_xor; struct page_list* journal; struct page_list* journal_io; } ;
struct async_submit_ctl {int dummy; } ;
struct TYPE_2__ {struct page* page; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_TX_XOR_ZERO_DST ; 
 int /*<<< orphan*/  BUG_ON (unsigned int) ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 size_t SECTOR_SHIFT ; 
 int /*<<< orphan*/  async_tx_issue_pending_all () ; 
 int /*<<< orphan*/  async_xor (struct page*,struct page**,unsigned int,int,size_t,struct async_submit_ctl*) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_journal_op ; 
 int /*<<< orphan*/  init_async_submit (struct async_submit_ctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct journal_completion*,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  page_list_location (struct dm_integrity_c*,unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int roundup (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  rw_section_mac (struct dm_integrity_c*,unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void xor_journal(struct dm_integrity_c *ic, bool encrypt, unsigned section,
			unsigned n_sections, struct journal_completion *comp)
{
	struct async_submit_ctl submit;
	size_t n_bytes = (size_t)(n_sections * ic->journal_section_sectors) << SECTOR_SHIFT;
	unsigned pl_index, pl_offset, section_index;
	struct page_list *source_pl, *target_pl;

	if (likely(encrypt)) {
		source_pl = ic->journal;
		target_pl = ic->journal_io;
	} else {
		source_pl = ic->journal_io;
		target_pl = ic->journal;
	}

	page_list_location(ic, section, 0, &pl_index, &pl_offset);

	atomic_add(roundup(pl_offset + n_bytes, PAGE_SIZE) >> PAGE_SHIFT, &comp->in_flight);

	init_async_submit(&submit, ASYNC_TX_XOR_ZERO_DST, NULL, complete_journal_op, comp, NULL);

	section_index = pl_index;

	do {
		size_t this_step;
		struct page *src_pages[2];
		struct page *dst_page;

		while (unlikely(pl_index == section_index)) {
			unsigned dummy;
			if (likely(encrypt))
				rw_section_mac(ic, section, true);
			section++;
			n_sections--;
			if (!n_sections)
				break;
			page_list_location(ic, section, 0, &section_index, &dummy);
		}

		this_step = min(n_bytes, (size_t)PAGE_SIZE - pl_offset);
		dst_page = target_pl[pl_index].page;
		src_pages[0] = source_pl[pl_index].page;
		src_pages[1] = ic->journal_xor[pl_index].page;

		async_xor(dst_page, src_pages, pl_offset, 2, this_step, &submit);

		pl_index++;
		pl_offset = 0;
		n_bytes -= this_step;
	} while (n_bytes);

	BUG_ON(n_sections);

	async_tx_issue_pending_all();
}