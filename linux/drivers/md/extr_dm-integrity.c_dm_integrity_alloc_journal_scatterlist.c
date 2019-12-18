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
struct scatterlist {int dummy; } ;
struct page_list {int /*<<< orphan*/  page; } ;
struct dm_integrity_c {unsigned int journal_sections; scalar_t__ journal_section_sectors; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int SECTOR_SHIFT ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  dm_integrity_free_journal_scatterlist (struct dm_integrity_c*,struct scatterlist**) ; 
 void* kvmalloc_array (unsigned int,int,int) ; 
 char* lowmem_page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_list_location (struct dm_integrity_c*,unsigned int,scalar_t__,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,char*,unsigned int) ; 

__attribute__((used)) static struct scatterlist **dm_integrity_alloc_journal_scatterlist(struct dm_integrity_c *ic,
								   struct page_list *pl)
{
	struct scatterlist **sl;
	unsigned i;

	sl = kvmalloc_array(ic->journal_sections,
			    sizeof(struct scatterlist *),
			    GFP_KERNEL | __GFP_ZERO);
	if (!sl)
		return NULL;

	for (i = 0; i < ic->journal_sections; i++) {
		struct scatterlist *s;
		unsigned start_index, start_offset;
		unsigned end_index, end_offset;
		unsigned n_pages;
		unsigned idx;

		page_list_location(ic, i, 0, &start_index, &start_offset);
		page_list_location(ic, i, ic->journal_section_sectors - 1,
				   &end_index, &end_offset);

		n_pages = (end_index - start_index + 1);

		s = kvmalloc_array(n_pages, sizeof(struct scatterlist),
				   GFP_KERNEL);
		if (!s) {
			dm_integrity_free_journal_scatterlist(ic, sl);
			return NULL;
		}

		sg_init_table(s, n_pages);
		for (idx = start_index; idx <= end_index; idx++) {
			char *va = lowmem_page_address(pl[idx].page);
			unsigned start = 0, end = PAGE_SIZE;
			if (idx == start_index)
				start = start_offset;
			if (idx == end_index)
				end = end_offset + (1 << SECTOR_SHIFT);
			sg_set_buf(&s[idx - start_index], va + start, end - start);
		}

		sl[i] = s;
	}

	return sl;
}