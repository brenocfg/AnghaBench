#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct journal_node {int dummy; } ;
struct TYPE_8__ {unsigned int logical_sector; unsigned int n_sectors; } ;
struct journal_io {TYPE_3__ range; struct journal_completion* comp; } ;
struct journal_entry {int dummy; } ;
struct journal_completion {int /*<<< orphan*/  comp; scalar_t__ in_flight; struct dm_integrity_c* ic; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct dm_integrity_c {unsigned int journal_section_entries; int sectors_per_block; int /*<<< orphan*/  bufio; TYPE_1__* sb; int /*<<< orphan*/  tag_size; scalar_t__ internal_hash; TYPE_2__ endio_wait; int /*<<< orphan*/  journal_io_mempool; struct journal_node* journal_tree; } ;
struct blk_plug {int dummy; } ;
typedef  unsigned int sector_t ;
typedef  scalar_t__ atomic_t ;
struct TYPE_6__ {unsigned int log2_sectors_per_block; } ;

/* Variables and functions */
 scalar_t__ ATOMIC_INIT (int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EILSEQ ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  TAG_WRITE ; 
 scalar_t__ access_journal_data (struct dm_integrity_c*,unsigned int,unsigned int) ; 
 struct journal_entry* access_journal_entry (struct dm_integrity_c*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  add_new_range (struct dm_integrity_c*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  atomic_inc (scalar_t__*) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  complete_copy_from_journal ; 
 int /*<<< orphan*/  complete_journal_op (struct journal_completion*) ; 
 int /*<<< orphan*/  copy_from_journal (struct dm_integrity_c*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct journal_io*) ; 
 int /*<<< orphan*/  crypto_shash_digestsize (scalar_t__) ; 
 int /*<<< orphan*/  dm_bufio_write_dirty_buffers_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_integrity_flush_buffers (struct dm_integrity_c*) ; 
 int /*<<< orphan*/  dm_integrity_io_error (struct dm_integrity_c*,char*,int) ; 
 int dm_integrity_rw_tag (struct dm_integrity_c*,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_newer_committed_node (struct dm_integrity_c*,struct journal_node*) ; 
 int /*<<< orphan*/  get_area_and_offset (struct dm_integrity_c*,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  get_data_sector (struct dm_integrity_c*,unsigned int,unsigned int) ; 
 unsigned int get_metadata_sector_and_offset (struct dm_integrity_c*,unsigned int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  integrity_sector_checksum (struct dm_integrity_c*,unsigned int,char*,char*) ; 
 unsigned int journal_entry_get_sector (struct journal_entry*) ; 
 int journal_entry_is_inprogress (struct journal_entry*) ; 
 scalar_t__ journal_entry_is_unused (struct journal_entry*) ; 
 int /*<<< orphan*/  journal_entry_set_unused (struct journal_entry*) ; 
 int /*<<< orphan*/  journal_entry_tag (struct dm_integrity_c*,struct journal_entry*) ; 
 scalar_t__ likely (int) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memcmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct journal_io* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct journal_io*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_journal_node (struct dm_integrity_c*,struct journal_node*) ; 
 int /*<<< orphan*/  remove_range_unlocked (struct dm_integrity_c*,TYPE_3__*) ; 
 int /*<<< orphan*/  restore_last_bytes (struct dm_integrity_c*,scalar_t__,struct journal_entry*) ; 
 int /*<<< orphan*/  rw_section_mac (struct dm_integrity_c*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_and_add_new_range (struct dm_integrity_c*,TYPE_3__*) ; 
 int /*<<< orphan*/  wait_for_completion_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wraparound_section (struct dm_integrity_c*,unsigned int*) ; 

__attribute__((used)) static void do_journal_write(struct dm_integrity_c *ic, unsigned write_start,
			     unsigned write_sections, bool from_replay)
{
	unsigned i, j, n;
	struct journal_completion comp;
	struct blk_plug plug;

	blk_start_plug(&plug);

	comp.ic = ic;
	comp.in_flight = (atomic_t)ATOMIC_INIT(1);
	init_completion(&comp.comp);

	i = write_start;
	for (n = 0; n < write_sections; n++, i++, wraparound_section(ic, &i)) {
#ifndef INTERNAL_VERIFY
		if (unlikely(from_replay))
#endif
			rw_section_mac(ic, i, false);
		for (j = 0; j < ic->journal_section_entries; j++) {
			struct journal_entry *je = access_journal_entry(ic, i, j);
			sector_t sec, area, offset;
			unsigned k, l, next_loop;
			sector_t metadata_block;
			unsigned metadata_offset;
			struct journal_io *io;

			if (journal_entry_is_unused(je))
				continue;
			BUG_ON(unlikely(journal_entry_is_inprogress(je)) && !from_replay);
			sec = journal_entry_get_sector(je);
			if (unlikely(from_replay)) {
				if (unlikely(sec & (unsigned)(ic->sectors_per_block - 1))) {
					dm_integrity_io_error(ic, "invalid sector in journal", -EIO);
					sec &= ~(sector_t)(ic->sectors_per_block - 1);
				}
			}
			get_area_and_offset(ic, sec, &area, &offset);
			restore_last_bytes(ic, access_journal_data(ic, i, j), je);
			for (k = j + 1; k < ic->journal_section_entries; k++) {
				struct journal_entry *je2 = access_journal_entry(ic, i, k);
				sector_t sec2, area2, offset2;
				if (journal_entry_is_unused(je2))
					break;
				BUG_ON(unlikely(journal_entry_is_inprogress(je2)) && !from_replay);
				sec2 = journal_entry_get_sector(je2);
				get_area_and_offset(ic, sec2, &area2, &offset2);
				if (area2 != area || offset2 != offset + ((k - j) << ic->sb->log2_sectors_per_block))
					break;
				restore_last_bytes(ic, access_journal_data(ic, i, k), je2);
			}
			next_loop = k - 1;

			io = mempool_alloc(&ic->journal_io_mempool, GFP_NOIO);
			io->comp = &comp;
			io->range.logical_sector = sec;
			io->range.n_sectors = (k - j) << ic->sb->log2_sectors_per_block;

			spin_lock_irq(&ic->endio_wait.lock);
			if (unlikely(!add_new_range(ic, &io->range, true)))
				wait_and_add_new_range(ic, &io->range);

			if (likely(!from_replay)) {
				struct journal_node *section_node = &ic->journal_tree[i * ic->journal_section_entries];

				/* don't write if there is newer committed sector */
				while (j < k && find_newer_committed_node(ic, &section_node[j])) {
					struct journal_entry *je2 = access_journal_entry(ic, i, j);

					journal_entry_set_unused(je2);
					remove_journal_node(ic, &section_node[j]);
					j++;
					sec += ic->sectors_per_block;
					offset += ic->sectors_per_block;
				}
				while (j < k && find_newer_committed_node(ic, &section_node[k - 1])) {
					struct journal_entry *je2 = access_journal_entry(ic, i, k - 1);

					journal_entry_set_unused(je2);
					remove_journal_node(ic, &section_node[k - 1]);
					k--;
				}
				if (j == k) {
					remove_range_unlocked(ic, &io->range);
					spin_unlock_irq(&ic->endio_wait.lock);
					mempool_free(io, &ic->journal_io_mempool);
					goto skip_io;
				}
				for (l = j; l < k; l++) {
					remove_journal_node(ic, &section_node[l]);
				}
			}
			spin_unlock_irq(&ic->endio_wait.lock);

			metadata_block = get_metadata_sector_and_offset(ic, area, offset, &metadata_offset);
			for (l = j; l < k; l++) {
				int r;
				struct journal_entry *je2 = access_journal_entry(ic, i, l);

				if (
#ifndef INTERNAL_VERIFY
				    unlikely(from_replay) &&
#endif
				    ic->internal_hash) {
					char test_tag[max(crypto_shash_digestsize(ic->internal_hash), ic->tag_size)];

					integrity_sector_checksum(ic, sec + ((l - j) << ic->sb->log2_sectors_per_block),
								  (char *)access_journal_data(ic, i, l), test_tag);
					if (unlikely(memcmp(test_tag, journal_entry_tag(ic, je2), ic->tag_size)))
						dm_integrity_io_error(ic, "tag mismatch when replaying journal", -EILSEQ);
				}

				journal_entry_set_unused(je2);
				r = dm_integrity_rw_tag(ic, journal_entry_tag(ic, je2), &metadata_block, &metadata_offset,
							ic->tag_size, TAG_WRITE);
				if (unlikely(r)) {
					dm_integrity_io_error(ic, "reading tags", r);
				}
			}

			atomic_inc(&comp.in_flight);
			copy_from_journal(ic, i, j << ic->sb->log2_sectors_per_block,
					  (k - j) << ic->sb->log2_sectors_per_block,
					  get_data_sector(ic, area, offset),
					  complete_copy_from_journal, io);
skip_io:
			j = next_loop;
		}
	}

	dm_bufio_write_dirty_buffers_async(ic->bufio);

	blk_finish_plug(&plug);

	complete_journal_op(&comp);
	wait_for_completion_io(&comp.comp);

	dm_integrity_flush_buffers(ic);
}